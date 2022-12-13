using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Mirror;
using UnityEngine.UI;

public class Room : NetworkBehaviour
{
    private void Start()
    {
        if (isServer)
        {
            FindObjectsOfType<Button>()[0].gameObject.SetActive(true);
        }
        else
        {
            FindObjectsOfType<Button>()[0].gameObject.SetActive(false);
        }
    }
    public void OnClickStartButton()
    {
        if (isServer)
        {
            GameRoomManager manager = NetworkManager.singleton as GameRoomManager;
            manager.ServerChangeScene("GamePlay");
        }
    }

    public void ExitRoom()
    {
        NetworkManager networkManager = GameRoomManager.singleton;
        if (networkManager.mode == NetworkManagerMode.Host)
        {
            networkManager.StopHost();
        }
        else if (networkManager.mode == NetworkManagerMode.ClientOnly)
        {
            networkManager.StopClient();
        }
    }
}
