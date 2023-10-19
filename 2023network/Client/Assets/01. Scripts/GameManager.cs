using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class GameManager : MonoBehaviour
{
	private static GameManager instance = null;
    public static GameManager Instance {
        get {
            if(instance == null)
                instance = GameObject.Find("GameManager")?.GetComponent<GameManager>();
            return instance;
        }
    }

    private const char PREFIX_TERMINATOR = ';';
    private const char PREFIX_ID = '$';
    private const char PREFIX_COMMA = ',';
    private const char PREFIX_COMMAND = '#';

    [SerializeField] TMP_InputField nicknameField;
    [SerializeField] TMP_InputField chatField;
    public string myID;

    [SerializeField] UserControl playerPrefab;
    public UserControl userController;

    private Dictionary<string, UserControl> remoteUsers;
    private Queue<string> commandQueue;

    private void Awake()
    {
        // if(instance == null)
        // {
        //     instance = this;
        //     DontDestroyOnLoad(gameObject);
        // }
        // else
        // {
        //     Destroy(gameObject);
        //     return;
        // }

        SocketModule.Instance = gameObject.AddComponent<SocketModule>();

        remoteUsers = new Dictionary<string, UserControl>();
        commandQueue = new Queue<string>();
    }

    private void Update()
    {
        ProcessQueue();
    }

    public void SendCommand(string cmd)
    {
        SocketModule.Instance.SendData(cmd);
        Debug.Log($"command sended : {cmd}");
    }
    
    public void QueueCommand(string cmd)
    {
        commandQueue.Enqueue(cmd);
    }

    public void ProcessQueue()
    {
        while(commandQueue.Count > 0)
        {
            string nextCommand = commandQueue.Dequeue();
            ProcessCommand(nextCommand);
        }
    }

    public void ProcessCommand(string cmd)
    {
        bool isMore = true;
        while(isMore)
        {
            Debug.Log($"Process cmd = {cmd}");

            int nameIdx = cmd.IndexOf(PREFIX_ID);
            string id = "";
            if(nameIdx > 0)
            {
                id = cmd.Substring(0, nameIdx);
            }

            int cmdIdx1 = cmd.IndexOf(PREFIX_COMMAND);
            if(cmdIdx1 > nameIdx)
            {
                int cmdIdx2 = cmd.IndexOf(PREFIX_COMMAND, cmdIdx1 + 1);
                if(cmdIdx2 > cmdIdx1)
                {
                    string command = cmd.Substring(cmdIdx1 + 1, cmdIdx2 - cmdIdx1 - 1);

                    string remain = "";
                    string nextCommand;
                    int endIdx = cmd.IndexOf(PREFIX_TERMINATOR, cmdIdx2 + 1);
                    if(endIdx > cmdIdx2)
                    {
                        remain = cmd.Substring(cmdIdx2 + 1, endIdx - cmdIdx2 - 1);
                        nextCommand = cmd.Substring(endIdx + 1);
                    }
                    else
                    {
                        nextCommand = cmd.Substring(cmdIdx2 + 1);
                    }

                    Debug.Log($"command={command} id={id} remain={remain} next={nextCommand}");

                    if(myID.CompareTo(id) != 0)
                    {
                        switch(command)
                        {
                            case "Enter":
                                AddUser(id);
                                break;
                            case "Move":
                                break;
                            case "Left":
                                UserLeft(id);
                                break;
                            case "Heal":
                                UserHeal(id);
                                break;
                            case "Damage":
                                break;
                        }
                    }
                    else
                        Debug.Log("Skip");

                    cmd = nextCommand;
                }
                else
                    isMore = false;
            }
            else
                isMore = false;
        }
    }

    private void SetMove(string id, string cmdMove)
    {
        if(remoteUsers.ContainsKey(id) == false)
            return;

        string[] args = cmdMove.Split(',');

        bool resultX = float.TryParse(args[0], out float x);
        bool resultY = float.TryParse(args[1], out float y);
        
        if(resultX && resultY)
            remoteUsers[id]?.SetTargetPos(new Vector3(x, y));
    }

    private void TakeDamage(string remain)
    {
        if(remoteUsers.ContainsKey(remain) == false && myID != remain)
            return;

        if(myID == remain)
            userController.DropHP(10);
        else
            remoteUsers[remain]?.DropHP(10);
    }

    private void AddUser(string id)
    {
        if(remoteUsers.ContainsKey(id))
            return;

        UserControl otherPlayer = Instantiate(playerPrefab, Vector3.zero, Quaternion.identity);
        otherPlayer.id = id;
        remoteUsers.Add(id, otherPlayer);
    }

    private void UserLeft(string id)
    {
        if(remoteUsers.ContainsKey(id) == false)
            return;

        Destroy(remoteUsers[id].gameObject);
        remoteUsers.Remove(id);
    }

    private void UserHeal(string id)
    {
        if(remoteUsers.ContainsKey(id) == false)
            return;

        remoteUsers[id]?.Revive();
    }

    public void OnLogin()
    {
        myID = nicknameField.text;
        userController.id = myID;

        if(myID.Length > 0)
        {
            SocketModule.Instance.Login(myID);
            nicknameField.text = "";
        }
    }

    public void OnLogout()
    {
        SocketModule.Instance.Logout();
        remoteUsers.Clear();
    }

    public void OnRevive()
    {
        userController.Revive();
        string data = "#Heal#";
        SendCommand(data);
    }

    public void OnMessage()
    {
        if(myID != null)
        {
            SocketModule.Instance.SendData(chatField.text);
            chatField.text = "";
        }
    }
}
