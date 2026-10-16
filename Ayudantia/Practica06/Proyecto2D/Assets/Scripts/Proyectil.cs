using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Proyectil : MonoBehaviour
{
    public float velocidadBase = 10f;
    public float tiempoVida = 2f;
    public int dano = 1;

    private Vector2 direccion;
    private float velocidadextra = 0f;

    public void Inicializar(Vector2 dir,float velocidadJugador)
    {
        direccion = dir.normalized;
        velocidadextra = velocidadJugador;
        Destroy(gameObject, tiempoVida);
    }

    private void Update()
    {
        float velocidadFinal = velocidadBase + velocidadextra;
        transform.position += (Vector3)(direccion * velocidadFinal * Time.deltaTime);
    }

    private void OnTriggerEnter2D(Collider2D col)
    {
        if (col.CompareTag("Enemigo"))
        {
            col.GetComponent<EnemigoIA>().RecibirDano(dano);
            Destroy(gameObject);
        }
        if (col.CompareTag("Pared") || col.CompareTag("Obstaculo"))
        {
            Destroy(gameObject);
        }

    }
}
