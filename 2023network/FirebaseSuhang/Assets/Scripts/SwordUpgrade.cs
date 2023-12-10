using TMPro;
using UnityEngine;

public class SwordUpgrade : MonoBehaviour
{
    [SerializeField] TextMeshProUGUI levelText;
    [SerializeField] TextMeshProUGUI percentageText;

    private int level = 1;
    private int maxLevel = 1;
    private float percentage = 100f;

    private void Awake()
    {
        SetLevel(1);
    }

    public void DoUpgrade()
    {
        if(Random.Range(0f, 100f) > percentage)
            SetLevel(1);
        else
            SetLevel(level + 1);
    }

    public void SetLevel(int i)
    {
        level = i;
        percentage = 100f / (float)level;

        if(maxLevel < level)
            maxLevel = level;
        
        levelText.text = $"Lv. {level} \n Top Level : {maxLevel} Lv";
        percentageText.text = $"{percentage}%";
    }
}
