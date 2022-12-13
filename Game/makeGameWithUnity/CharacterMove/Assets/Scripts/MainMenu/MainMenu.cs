using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Mirror;

public class MainMenu : MonoBehaviour
{
    
    public void CreateRoom()
    {
        GameRoomManager.singleton.StartHost();
    }

    public void EnterRoom()
    {
        GameRoomManager.singleton.StartClient();
    }
}
