using System.Text;
using UnityEngine;

public class PlayerAttack : MonoBehaviour
{
    [SerializeField] float attackRadius = 3.5f;
    private int playerLayer = 1 << 7;

    private void Update()
    {
        if(Input.GetMouseButtonDown(0))
            GameManager.Instance.SendCommand($"#Attack#{DectectPlayers()}");
    }

    private string DectectPlayers()
    {
        StringBuilder players = new StringBuilder();
        Collider2D[] others = Physics2D.OverlapCircleAll(transform.position, attackRadius, playerLayer);

        for(int i = 0; i < others.Length; i++)
        {
            UserControl player = others[i].GetComponent<UserControl>();
            if(player != null)
                players.Append($"{player.id},");
        }

        return players.ToString();
    }
}
