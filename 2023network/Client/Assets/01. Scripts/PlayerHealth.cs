using UnityEngine;
using UnityEngine.UI;

public class PlayerHealth : MonoBehaviour
{
    private Camera mainCam;
    private Transform hpBarTrm;
    private Image hpBar;

    private int hp = 0;
    public int HP => hp;

    private float lastUpdateTime = 0;

    private void Awake()
    {
        hpBarTrm = GameObject.Find("Canvas/HPBarBG").transform;
        hpBar = hpBarTrm.Find("HPBar").GetComponent<Image>();
    }

    private void Start()
    {
        mainCam = Camera.main;
        hp = 100;
    }

    private void Update()
    {
        if(lastUpdateTime + 1f < Time.time)
        {
            FixHP(-1);
            lastUpdateTime = Time.time;
        }
    }

    private void FixedUpdate()
    {
        Vector3 pos = mainCam.WorldToScreenPoint(transform.position);
        pos.y += 100f;

        hpBarTrm.position = pos;
    }

    public void SetHP(int hp)
    {
        this.hp = hp;
        hpBar.fillAmount = hp / (float)100;
    }

    public void FixHP(int amount)
    {
        this.hp -= hp;
        hpBar.fillAmount = hp / (float)100;
    }
}
