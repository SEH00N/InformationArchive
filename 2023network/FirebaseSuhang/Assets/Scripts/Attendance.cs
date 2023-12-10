using System;
using TMPro;
using UnityEngine;

public class Attendance : MonoBehaviour
{
    [SerializeField] SwordUpgrade upgrade;
    [SerializeField] TextMeshProUGUI logText;

	private void Start()
    {
        int lastAttendace = PlayerPrefs.GetInt("Attendance", -1);
        int contAttendance = 0;
        int now = DateTime.Now.Day;

        if(lastAttendace != now)
        {
            logText.text += $"일일 보상!\n오늘의 기분이 조금 좋아집니다.\n";
            if(Mathf.Abs(lastAttendace - now) == 1)
                contAttendance = PlayerPrefs.GetInt("ContAttendance");

            contAttendance++;
            PlayerPrefs.SetInt("ContAttendance", contAttendance);
            logText.text += $"{contAttendance}일 째 연속 접속 중!\n검 레벨 ${contAttendance}만큼 늘려드림";
            upgrade.SetLevel(contAttendance + 1);
        }
        else
        {
            logText.text += $"내일도 접속 가자구~\n";
        }

        PlayerPrefs.SetInt("Attendance", now);
    }
}
