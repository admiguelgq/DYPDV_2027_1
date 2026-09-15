using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ControlJugador : MonoBehaviour
{
    public float velocidadActual = 0f;
    public float velocidadMax = 5f;
    public float aceleracion = 10f;

    public float velocidadVertical = 0f;
    public float gravedad = -20f;

    public float tiempoMaxSalto = 0.2f;
    private float tiempoSaltoActual = 0f;

    private float tiempoAnterior;

    void Update()
    {
        float delta = Time.time - tiempoAnterior;
        tiempoAnterior = Time.time;
    }
}
