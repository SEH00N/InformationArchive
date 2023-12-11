using Firebase;
using Firebase.Auth;
using Firebase.Database;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;
using TMPro;
using UnityEngine;
using UnityEngine.SceneManagement;

public class AuthManager : Singleton<AuthManager>
{
    [Header("Firebase")]
    public FirebaseAuth auth; //���� ���� ��ü
    public FirebaseUser User; //�����
    public DatabaseReference DBref; //�����ͺ��̽� �ν��Ͻ�

    [Header("Login")]
    public TMP_InputField emailLoginField;
    public TMP_InputField passwordLoginField;
    public TMP_Text warningLoginText;

    [Header("Register")]
    public TMP_InputField emailRegisterField;
    public TMP_InputField userNameRegisterField;
    public TMP_InputField passwordRegisterField;
    public TMP_InputField passwordCheckRegisterField;
    public TMP_Text warningRegisterText;

    public TMP_Text userNameText;
    public TMP_Text userInfoText;
    public TMP_InputField friendField;
    private string strWeather;
    private string strLastLogin;

    private void Awake()
    {
        Firebase.FirebaseApp.CheckAndFixDependenciesAsync().ContinueWith(task =>
        {
            var dependencyStatus = task.Result;
            if (dependencyStatus == Firebase.DependencyStatus.Available)
            {
                // Create and hold a reference to your FirebaseApp,
                // where app is a Firebase.FirebaseApp property of your application class.
                auth = FirebaseAuth.DefaultInstance;
                DBref = FirebaseDatabase.DefaultInstance.RootReference;

                // Set a flag here to indicate whether Firebase is ready to use by your app.
            }
            else
            {
                UnityEngine.Debug.LogError(System.String.Format(
                  "Could not resolve all Firebase dependencies: {0}", dependencyStatus));
                // Firebase Unity SDK is not safe to use here.
            }
        });
    }

    private IEnumerator Register(string email, string password, string userName)
    {
        if (userName == "")
        {
            warningRegisterText.text = "Missing Username";
        }
        else if (passwordRegisterField.text != passwordCheckRegisterField.text)
        {
            warningRegisterText.text = "Password does not Match!";
        }
        else
        {
            var task = auth.CreateUserWithEmailAndPasswordAsync(email, password);
            yield return new WaitUntil(() => task.IsCompleted);

            if (task.Exception != null)
            {
                Debug.LogWarning(message: $"Failed to Register:{task.Exception}");
                FirebaseException firebaseEx = task.Exception.GetBaseException() as FirebaseException;
                AuthError errorcode = (AuthError)firebaseEx.ErrorCode;

                string message = "Register Failed!";
                switch (errorcode)
                {
                    case AuthError.MissingEmail:
                        message = "Missing Email";
                        break;
                    case AuthError.MissingPassword:
                        message = "Missing Password";
                        break;
                    case AuthError.WeakPassword:
                        message = "Weak Password";
                        break;
                    case AuthError.EmailAlreadyInUse:
                        message = "Email Already In Use";
                        break;
                }
                warningRegisterText.text = message;

            }
            else
            {
                User = task.Result.User;
                if(User != null)
                {
                    FirebaseUser user = auth.CurrentUser;
                    if(user != null)
                    {
                        UserProfile profile = new UserProfile { DisplayName = userName };
                        var profileTask = user.UpdateUserProfileAsync(profile);
                        yield return new WaitUntil(() => profileTask.IsCompleted);
                        if(profileTask.Exception != null)
                        {
                            Debug.LogWarning(message:$"Failed to register:{profileTask.Exception}");
                            FirebaseException profileEx= profileTask.Exception.GetBaseException() as FirebaseException;
                            AuthError profileErrorCode = (AuthError)profileEx.ErrorCode;
                            warningRegisterText.text = "Username Set Failed!";
                        }
                        else
                        {
                            UIManager.Instance.LoginPanel();
                            Debug.Log("User Profile Updated Successfully");
                            warningRegisterText.text = "";
                            StartCoroutine(SaveUserName());
                            StartCoroutine(SaveRewardData());
                        }
                    }
                }

            }

        }

    }

    public void OnRegister()
    {
        StartCoroutine(Register(emailRegisterField.text, passwordRegisterField.text, userNameRegisterField.text));
    }

    private IEnumerator Login(string email, string password)
    {
        var task = auth.SignInWithEmailAndPasswordAsync(email, password);
        yield return new WaitUntil(() => task.IsCompleted);
        
        if (task.Exception != null)
        {
            Debug.LogWarning(message: $"Failed to Login:{task.Exception}");
            FirebaseException firebaseEx = task.Exception.GetBaseException() as FirebaseException;
            AuthError errorcode = (AuthError)firebaseEx.ErrorCode;

            string message = "Login Failed!";
            switch (errorcode)
            {
                case AuthError.MissingEmail:
                    message = "Missing Email";
                    break;
                case AuthError.MissingPassword:
                    message = "Missing Password";
                    break;
                case AuthError.WrongPassword:
                    message = "Wrong Password";
                    break;
                case AuthError.InvalidEmail:
                    message = "Invalid Email";
                    break;
                case AuthError.UserNotFound:
                    message = "Account does not Exist";
                    break;
            }
            warningLoginText.text = message;
        }
        else
        {
            User = task.Result.User;
            Debug.Log($"User Signed in Successfully: {User.Email}, {User.DisplayName}");
            warningLoginText.text = "";

            //�� ����� �� ���� �̺�Ʈ ȣ��
            DBref.Child("users").Child(User.UserId).Child("LastLogin").ValueChanged += LoadLastLogin;
            friendField.text = User.UserId;

            UIManager.Instance.CloseLogin();

            var userTask = DBref.Child("users").GetValueAsync();
            yield return new WaitUntil(() => userTask.IsCompleted);
            StringBuilder infoBuilder = new StringBuilder();
            foreach(var i in userTask.Result.Value as Dictionary<string, object>)
                infoBuilder.Append($"{i.Key.ToString()}\n");
            userInfoText.text = infoBuilder.ToString();
            // StartCoroutine(LoadUserName());
            // StartCoroutine(SaveLoginData());
            // StartCoroutine(LoadWeather());
            // SceneManager.LoadScene("GameScene");
        }
    }

    private void LoadLastLogin(object sender, ValueChangedEventArgs e)
    {
        if(e.DatabaseError != null)
        {
            Debug.LogError(e.DatabaseError.Message);
            return;
        }
        else
        {
            DBref.Child("users").Child(User.UserId).Child("RewardLogin")
                .GetValueAsync().ContinueWith(task =>
                {
                    if (task.IsCompleted)
                    {
                        DataSnapshot snapshot = task.Result;
                        if(snapshot!=null && snapshot.Value != null)
                        {
                            strLastLogin = snapshot.Value.ToString();
                            Debug.Log($"Reward Login :{strLastLogin}");
                        }
                    }
                });
        }
    }

    public void OnRewardButton()
    {
        string date = GetNow();
        // date2 = DateTime.Now.ToString("yyyyMMddHHmmss");
        if (strLastLogin.Substring(0, 12).CompareTo(date.Substring(0, 12)) < 0)
        {
            strLastLogin = date;
            DBref.Child("users").Child(User.UserId).Child("RewardLogin").SetValueAsync(date)
                .ContinueWith(task =>
                {
                    if (task.IsCompleted)
                    {
                        Debug.Log($"Reward LoginDate Updated:{date}");
                    }
                });
            Debug.Log("���� ����");
        }

    }

    public void LoginButton()
    {
        StartCoroutine(Login(emailLoginField.text, passwordLoginField.text));
    }

    private IEnumerator SaveUserName()
    {
        var DBTask = DBref.Child("users").Child(User.UserId).Child("UserName")
            .SetValueAsync(userNameRegisterField.text);
        yield return new WaitUntil(() => DBTask.IsCompleted);
        if (DBTask.Exception != null)
        {
            Debug.LogWarning($"Save Task failed with {DBTask.Exception}");
        }
        else Debug.Log("Save Completed");
    }

    private IEnumerator LoadUserName()
    {
        var DBTask = DBref.Child("users").Child(User.UserId).Child("UserName")
            .GetValueAsync();
        yield return new WaitUntil(() => DBTask.IsCompleted);
        if (DBTask.Exception != null)
        {
            Debug.LogWarning($"Load Task failed with {DBTask.Exception}");
        }
        else
        {
            DataSnapshot snapshot = DBTask.Result;
            Debug.Log("Load Completed");
            userNameText.text = $"Username: {snapshot.Value}";
        }
    }

    public IEnumerator LoadWeather()
    {
        var DBTask = DBref.Child("Weather").GetValueAsync();
        yield return new WaitUntil(() => DBTask.IsCompleted);
        if (DBTask.Exception != null)
        {
            Debug.LogWarning($"Load Task failed with {DBTask.Exception}");
        }
        else
        {
            DataSnapshot snapshot = DBTask.Result;
            if(snapshot!=null && snapshot.Value != null)
            {
                Debug.Log("Load Completed");
                strWeather = snapshot.Value.ToString();
            }
        }
        UIManager.Instance.StartGame();
    }

    public string GetWeather()
    {
        return strWeather;
    }

    //���� ȸ������ ����� ���� �ʱ�ȭ
    private IEnumerator SaveRewardData()
    {
        var DBTask = DBref.Child("users").Child(User.UserId).Child("RewardLogin")
            .SetValueAsync("00000000000000");
        yield return new WaitUntil(() => DBTask.IsCompleted);
        if (DBTask.Exception != null)
        {
            Debug.LogWarning($"Failed to save task with {DBTask.Exception}");
        }
        else
        {
            Debug.Log("Reward Data Initailized");
        }
    }

    public string GetNow()
    {
        return DateTime.Now.ToString("yyyyMMddHHmmss");
    }
    private IEnumerator SaveLoginData()
    {
        string currentDateTime = GetNow();
        var DBTask = DBref.Child("users").Child(User.UserId).Child("LastLogin").SetValueAsync(currentDateTime);
        yield return new WaitUntil(() => DBTask.IsCompleted);

        if (DBTask.Exception != null)
        {
            Debug.LogWarning(message: $"Failed to Save task with {DBTask.Exception}");

        }
        else
        {
            Debug.Log("Login Date update: " + currentDateTime);
        }
    }

    public void ChangePassword()
    {
        if(emailLoginField.text.Contains('@'))
            StartCoroutine(ChangePasswordCoroutine());
        else
            emailLoginField.text = "Enter Email Before Change Password";
    }

    private IEnumerator ChangePasswordCoroutine()
    {
        var task = auth.SendPasswordResetEmailAsync(emailLoginField.text);
        yield return new WaitUntil(() => task.IsCompleted);
        emailLoginField.text = "Check Email to Change Password";
    }

    public void AddFriend()
    {
        if(string.IsNullOrEmpty(friendField.text))
            return;

        StartCoroutine(AddFriendCoroutine());           
    }

    private IEnumerator AddFriendCoroutine()
    {
        var task = DBref.Child("users").Child(User.UserId).Child("Friends").GetValueAsync();
        yield return new WaitUntil(() => task.IsCompleted);

        var snapshot = task.Result;
        if(snapshot.Value == null)
            DBref.Child("users").Child(User.UserId).Child("Friends").SetValueAsync(friendField.text);
        else if(task.Result.Value.ToString().Contains(friendField.text) == false)
            DBref.Child("users").Child(User.UserId).Child("Friends").SetValueAsync($"{task.Result.Value.ToString()},{friendField.text}");
    }
}