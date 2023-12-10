using System.Collections;
using System.Threading.Tasks;
using Firebase.Database;
using TMPro;
using UnityEngine;

public class EventManager : MonoBehaviour
{
    [SerializeField] SwordUpgrade upgrade;
    [SerializeField] TextMeshProUGUI logText;

	private DatabaseReference db;

    private void Awake()
    {
        db = FirebaseDatabase.DefaultInstance.RootReference;
    }

    private IEnumerator Start()
    {
        var task = db.Child("event").GetValueAsync();
        yield return new WaitUntil(() => task.IsCompleted);

        DataSnapshot snapshot = task.Result;
        upgrade.SetLevel(int.Parse(snapshot.Value.ToString()));

        logText.text += $"이벤트 중임!! {snapshot.Value}레벨 올려드림\n";
    }
}
