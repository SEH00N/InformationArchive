using UnityEngine;

public class PlayerMovement : MonoBehaviour
{
    [SerializeField] float speed;

    private Camera mainCam;
    private Vector3 targetPos;

    private void Awake()
    {
        mainCam = Camera.main;
    }

    private void Start()
    {
        targetPos = transform.position;
    }

	private void Update()
    {
        if(Input.GetMouseButtonDown(1))
        {
            targetPos = mainCam.ScreenToWorldPoint(Input.mousePosition);
            targetPos.z = 0;
        }
    
        if((targetPos - transform.position).magnitude > 0.1f)
        {
            Vector3 dir = targetPos - transform.position;
            transform.position += dir.normalized * speed * Time.deltaTime;
        }
    }
}
