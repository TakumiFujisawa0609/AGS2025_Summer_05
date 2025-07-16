#pragma once

#include <string>
#include <array>
#include <memory>

class Player;
class DateTimeManager;

class GameHUD
{
public:
    GameHUD(void);
    ~GameHUD(void);

    void Init(std::shared_ptr<Player> player, DateTimeManager* dateTimeManager);
    void Update(void);
    void Draw(void);

private:
    std::shared_ptr<Player> player_;           // プレイヤーへの参照
    DateTimeManager* dateTimeManager_;         // 日付・時間管理への参照

    int uiFrameHandle_;

    int maxCompleteMessageTimer_;

    int moneyIconHandle_;                      // 所持金アイコン
    std::array<int, 4> timeIcons_;             // 時間帯アイコン（朝・昼・夕・夜）

    enum TIME_ICON_INDEX
    {
        MORNING = 0,
        DAY,
        EVENING,
        NIGHT
    };
};
