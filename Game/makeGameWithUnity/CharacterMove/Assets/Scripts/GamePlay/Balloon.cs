using Mirror;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SubsystemsImplementation;

public class Balloon : MonoBehaviour
{
    private void OnTriggerEnter(Collider other)
    {
        Combat targetCombat = other.gameObject.GetComponent<Combat>();

        if (targetCombat != null)
        {
            MeshRenderer[] meshRenderers = targetCombat.GetComponentsInChildren<MeshRenderer>();
            for(int i = 0; i < meshRenderers.Length; i++)
            {
                meshRenderers[i].material.color = Color.red;
            }

            int damage = 10;
            targetCombat.TakeDamage(damage);

            StopAllCoroutines();
            StartCoroutine("ReturnMeshColor", meshRenderers);
        }
    }

    IEnumerator ReturnMeshColor(MeshRenderer[] meshRenderers)
    {
        yield return new WaitForSeconds(2);

        for (int i = 0; i < meshRenderers.Length; i++)
        {
            meshRenderers[i].material.color = Color.white;
        }
    }
    public void DestroyBalloon()
    {
        Destroy(gameObject);
    }
}
