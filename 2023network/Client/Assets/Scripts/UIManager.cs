using UnityEngine;

public class UIManager : Singleton<UIManager>
{
    public GameObject loginUI;
    public GameObject registerUI;
    public GameObject playUI;
    public GameObject user;

	public void LoginScreen()
    {
        loginUI.SetActive(true);
        registerUI.SetActive(false);
    }

    public void RegisterScreen()
    {
        loginUI.SetActive(false);
        registerUI.SetActive(true);
    }

    public void CloseLogin()
    {
        loginUI.SetActive(false);
        user.SetActive(true);
        registerUI.SetActive(true);
    }
}
