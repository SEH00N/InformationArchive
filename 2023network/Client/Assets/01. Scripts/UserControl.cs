using UnityEngine;

public class UserControl : MonoBehaviour
{
    public string id;

    private PlayerMovement movement;
    private PlayerHealth health;

    private void Awake()
    {
        movement = GetComponent<PlayerMovement>();
        health = GetComponent<PlayerHealth>();
    }

	public void SetTargetPos(Vector3 pos)
    {   
        movement.SetTargetPos(pos);
    }

    public void SetHP(int hp)
    {
        health.SetHP(hp);
    }

    public void DropHP(int drop)
    {
        health.FixHP(-drop);
    }

    public void Revive()
    {
        health.SetHP(100);
    }

    public int GetHP() => health.HP;
}
