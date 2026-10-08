using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UIElements;

public class PlayerMovementAnim : MonoBehaviour
{
    Animator anim;
    CharacterController controller;
    public Transform cameraTransform;
    void Start()
    {
        anim = GetComponent<Animator>();
        controller = GetComponentInParent<CharacterController>();
    }
    void Update()
    {
        float x = Input.GetAxis("Horizontal");
        float z = Input.GetAxis("Vertical");
        Vector3 camForward = cameraTransform.forward;
        Vector3 camRight = cameraTransform.right;
        camForward.y = 0f;
        camRight.y = 0f;
        camForward.Normalize();
        camRight.Normalize();
        Vector3 moveDir = camForward * z + camRight * x;
        Vector3 clampedMoveDir = Vector3.ClampMagnitude(moveDir, 1f);

        controller.Move(moveDir * Time.deltaTime * 3f);

        float speedValue = moveDir.magnitude;
        anim.SetFloat("Speed", speedValue);


        if (moveDir.magnitude > 0.1f)
        {
            Quaternion targetRotation = Quaternion.LookRotation(moveDir);
            transform.root.rotation = Quaternion.Slerp(
            transform.root.rotation,
            targetRotation,
            Time.deltaTime * 10f
            );
        }
        if (Input.GetButtonDown("Jump"))
        {
            anim.SetBool("IsJumping", true);
        }
        else
        {
            anim.SetBool("IsJumping", false);
        }
    }
}
