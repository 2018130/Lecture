using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Mirror;
using UnityEngine.UI;
using System.Globalization;
using Unity.VisualScripting;

public class GameRoomManager : NetworkRoomManager
{
    int teamSize = 5;
    List<PlayerText> teamA = new List<PlayerText>();
    public List<PlayerText> TeamA
    {
        get { return teamA; }
    }
    List<PlayerText> teamB = new List<PlayerText>();
    public List<PlayerText> TeamB
    {
        get { return teamB; }
    }

    private void Start()
    {
        base.Start();
        showRoomGUI = false;
    }
    public override void OnRoomServerConnect(NetworkConnectionToClient conn)
    {
        base.OnRoomServerConnect(conn);

        int currentUserSize = teamA.Count + teamB.Count;
        if(teamA.Count <= teamSize && currentUserSize % 2 == 0)
        {
            GameObject spawnObj = Instantiate(spawnPrefabs[0]);
            spawnObj.GetComponent<PlayerText>().Team = 'A';
            spawnObj.GetComponent<PlayerText>().Number = teamA.Count;
            teamA.Add(spawnObj.GetComponent<PlayerText>());
            NetworkServer.Spawn(spawnObj, conn);
        }
        else if(teamB.Count <= teamSize)
        {
            GameObject spawnObj = Instantiate(spawnPrefabs[0]);
            spawnObj.GetComponent<PlayerText>().Team = 'B';
            spawnObj.GetComponent<PlayerText>().Number = teamB.Count;
            teamB.Add(spawnObj.GetComponent<PlayerText>());
            NetworkServer.Spawn(spawnObj, conn);
        }
        else
        {
            conn.Disconnect();
        }
    }
}
