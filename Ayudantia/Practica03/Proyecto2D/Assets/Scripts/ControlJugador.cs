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

    private Jugador jugador;

    public float desaceleracion = 8f;
    public float gravedadCaida = -30f;

    public float tiempoCoyote = 0.1f;
    public float tiempoBufferSalto = 0.1f;

    private float coyoteTimer = 0f;
    private float bufferTimer = 0f;

    private void Awake()
    {
        jugador = GetComponent<Jugador>();
    }

    void Update()
    {
        float delta = Time.time - tiempoAnterior;
        tiempoAnterior = Time.time;

        float h = Input.GetAxis("Horizontal");
        velocidadActual += aceleracion * h * delta;
        velocidadActual = Mathf.Clamp(velocidadActual, -velocidadMax, velocidadMax);
   
        if (h == 0)
        {
            if (velocidadActual > 0)
                velocidadActual -= desaceleracion * delta;
            else if (velocidadActual<0)
                velocidadActual += desaceleracion * delta;

            if (Mathf.Abs(velocidadActual) < 0.1f)
                velocidadActual = 0;
        }

        transform.position += new Vector3(velocidadActual * delta, 0, 0);

        if (jugador.enSuelo)
            coyoteTimer = tiempoCoyote;
        else
            coyoteTimer -= delta;

        if (Input.GetAxis("Jump") > 0)
            bufferTimer = tiempoBufferSalto;
        else
            bufferTimer -= delta;


        if (bufferTimer > 0 && coyoteTimer > 0)
        {
            velocidadVertical = 10f;
            jugador.enSuelo = false;
            tiempoSaltoActual = 0;
            coyoteTimer = 0;
            bufferTimer = 0;

        }

        if (!jugador.enSuelo && Input.GetAxis("Jump") > 0)
        {
            if (tiempoSaltoActual < tiempoMaxSalto)
            {
                velocidadVertical += 20f * delta;
                tiempoSaltoActual += delta;
            }
        }

        if (Input.GetAxis("Jump") == 0)
        {
            tiempoSaltoActual = tiempoMaxSalto;
        }
        if (jugador.enSuelo)
        {
            velocidadVertical = 0;
        }
        else
        {
            velocidadVertical += gravedad * delta;
        }
        transform.position += new Vector3(0, velocidadVertical * delta, 0);
    }
}
