using Mirror;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Combat : NetworkBehaviour
{
    AudioSource audioSource;
    [SerializeField]
    GameObject balloonPrefab;
    [SerializeField]
    float balloonPower = 100f;

    const int maxHealth = 100;
    [SyncVar]
    int health = maxHealth;

    private void Start()
    {
        audioSource = GetComponent<AudioSource>();
    }

    private void Update()
    {
        if (isOwned)
        {
            if (Input.GetMouseButtonDown(0))
            {
                CmdFire();
                audioSource.clip = Resources.Load<AudioClip>("shotAudioClip");
                audioSource.Play();
            }
        }
    }

    [Command]
    public void CmdFire()
    {
        Vector3 forwardDirVector = new Vector3(Mathf.Sin(transform.rotation.eulerAngles.y * Mathf.PI / 180), 0, Mathf.Cos(transform.rotation.eulerAngles.y * Mathf.PI / 180)).normalized;
        GameObject balloon = Instantiate(balloonPrefab, transform.position + forwardDirVector * 0.5f + new Vector3(0, 0.5f, 0), Quaternion.identity);
        balloon.GetComponent<Rigidbody>().AddForce(forwardDirVector * balloonPower);

        NetworkServer.Spawn(balloon);

        StartCoroutine("DestroyBalloon", balloon);
    }

    [ClientRpc]
    public void RpcRespawn()
    {
        if (isOwned)
        {
            MyGameRoomPlayer[] myGamePlayers = FindObjectsOfType<MyGameRoomPlayer>();

            for (int i = 0; i < myGamePlayers.Length; i++)
            {
                if (myGamePlayers[i].isOwned)
                {
                    transform.position = new Vector3(25, 0 + i, 1);
                }
                else
                {
                    transform.position = new Vector3(-25, 0 + i, 1);
                }

            }
        }
    }

    IEnumerator DestroyBalloon(GameObject balloon)
    {
        yield return new WaitForSeconds(4);

        balloon.GetComponent<Balloon>().DestroyBalloon();
    }

    public void TakeDamage(int amount)
    {
        if (isServer)
        {
            health -= amount;

            if (health <= 0) {
                health = maxHealth;
                RpcRespawn();
            }
        }
    }
}
