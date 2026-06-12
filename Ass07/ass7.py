from typing import List, Dict, Set
from collections import defaultdict
from functools import reduce

def total_time_per_user(logs: List[Dict]) -> Dict[str, float]:
    user_times = defaultdict(float)
    reduce(lambda _, log: user_times.__setitem__(log["user"], user_times[log["user"]] + log["duration"]), logs, None)
    return dict(user_times)

def most_active_users(logs: List[Dict], k: int) -> List[str]:
    user_times = total_time_per_user(logs)
    return [user for user, _ in sorted(user_times.items(), key=lambda x: x[1], reverse=True)[:k]]

def unique_actions(logs: List[Dict]) -> Set[str]:
    return {log["action"] for log in logs}


if __name__ == "__main__":
    logs = [
        {"user": "101", "action": "YouTube", "duration": 2.5},
        {"user": "102", "action": "Instagram", "duration": 1.0},
        {"user": "101", "action": "WhatsApp", "duration": 1.2},
        {"user": "103", "action": "YouTube", "duration": 3.0},
        {"user": "102", "action": "YouTube", "duration": 2.0},
    ]

    print("Total Time Per User:", total_time_per_user(logs))
    print("Most Active Users (Top 2):", most_active_users(logs, 2))
    print("Unique Actions:", unique_actions(logs))