using Mirror;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PlayerText : NetworkBehaviour
{
    [SyncVar]
    char team;
    public char Team
    {
        get { return team; }
        set { team = value; }
    }

    [SyncVar]
    int number;
    public int Number
    {
        get { return number; }
        set { number = value; }
    }

    // Start is called before the first frame update
    void Start()
    {
        transform.SetParent(FindObjectOfType<Canvas>().transform);
        SetPlayerPanelPosition();
    }

    public void SetPlayerPanelPosition()
    {
        int teamAStartPosY = 30;
        int teamBStartPosY = -110;
        int paddingY = 15;
        if (team == 'A')
        {
            GetComponent<RectTransform>().anchoredPosition = new Vector2(0, teamAStartPosY - paddingY * number);
        }
        else if (team == 'B')
        {
            GetComponent<RectTransform>().anchoredPosition = new Vector2(0, teamBStartPosY + paddingY * number);
        }

        GetComponent<Text>().text = "Player" + number.ToString();
        if (isOwned)
        {
            GetComponent<Text>().text += "(me)";
        }
    }
}
