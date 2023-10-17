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
            SetTargetPos(Input.mousePosition);
    
        if((targetPos - transform.position).magnitude > 0.1f)
        {
            Vector3 dir = targetPos - transform.position;
            transform.position += dir.normalized * speed * Time.deltaTime;
        }
    }

    public void SetTargetPos(Vector3 pos)
    {
        targetPos = mainCam.ScreenToWorldPoint(pos);
        targetPos.z = 0;
    }
}
