using Mirror;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Mover : NetworkBehaviour
{
    Animator animator;
    float speed = 5f;
    float turnSpeed = 30f;
    float jumpForce = 10f;
    int teamId = -1;

    Vector3 cameraOffset;
    public int TeamId
    {
        get { return teamId; }
        set { teamId = value; }
    }

    private void Start()
    {
        if (isOwned)
        {
            Camera.main.transform.SetParent(transform);
            animator = GetComponentInChildren<Animator>();
        }

        MyGameRoomPlayer[] myGamePlayers = FindObjectsOfType<MyGameRoomPlayer>();
        cameraOffset = new Vector3(0, 2f, -2f);
        for (int i = 0; i < myGamePlayers.Length; i++)
        {
            if (myGamePlayers[i].isOwned)
            {
                teamId = i % 2;
                if (teamId == 0)
                {
                    transform.position = new Vector3(25, 0 + i, 1);
                    Camera.main.transform.position = transform.position + cameraOffset;
                }
                else
                {
                    transform.position = new Vector3(-25, 0 + i, 1);
                    Camera.main.transform.position = transform.position + cameraOffset;
                }
            }
        }
    }
    

    // Update is called once per frame
    void Update()
    {
        if (isOwned)
        {
            float h = Input.GetAxis("Horizontal");
            float v = Input.GetAxis("Vertical");
            Vector3 moveVector = new Vector3(h, 0, v).normalized;
            transform.Translate(moveVector * Time.deltaTime * speed, Space.Self);
            animator.SetFloat("MoveX", h);
            animator.SetFloat("MoveY", v);

            float yAngle = -Input.GetAxis("Mouse Y") * turnSpeed * Time.deltaTime;
            float xAngle = Input.GetAxis("Mouse X") * turnSpeed * Time.deltaTime;
            transform.rotation = Quaternion.Euler(new Vector3(transform.rotation.eulerAngles.x, transform.rotation.eulerAngles.y + xAngle, 0));

            //Camera.main.transform.position = transform.position + new Vector3(Mathf.Sin(transform.rotation.eulerAngles.y * Mathf.PI / 180) * cameraOffset.z, cameraOffset.y
            //    ,Mathf.Cos(transform.rotation.eulerAngles.y * Mathf.PI / 180) * cameraOffset.z);
            float maxYAngle = 30f;
            float minYAngle = 5f;
            float newCameraYAngle = Mathf.Clamp(Camera.main.transform.rotation.eulerAngles.x + yAngle, minYAngle, maxYAngle);
            Camera.main.transform.rotation = Quaternion.Euler(new Vector3(newCameraYAngle,
                Camera.main.transform.rotation.eulerAngles.y, Camera.main.transform.rotation.eulerAngles.z));

            if (Input.GetMouseButtonDown(0))
            {
                animator.SetTrigger("Attack");
            }
        }
    }
}
