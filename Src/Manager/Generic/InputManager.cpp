#include "InputManager.h"
#include <DxLib.h>

InputManager* InputManager::instance_ = nullptr;

void InputManager::CreateInstance(void)
{
    if (instance_ == nullptr)
    {
        instance_ = new InputManager();
    }
    instance_->Init();
}

InputManager& InputManager::GetInstance(void)
{
    if (instance_ == nullptr)
    {
        InputManager::CreateInstance();
    }
    return *instance_;
}

void InputManager::Init(void)
{
    InputManager::GetInstance().Add(KEY_INPUT_SPACE);

    InputManager::GetInstance().Add(KEY_INPUT_W);
    InputManager::GetInstance().Add(KEY_INPUT_S);
    InputManager::GetInstance().Add(KEY_INPUT_A);
    InputManager::GetInstance().Add(KEY_INPUT_D);

    InputManager::GetInstance().Add(KEY_INPUT_UP);
    InputManager::GetInstance().Add(KEY_INPUT_DOWN);
    InputManager::GetInstance().Add(KEY_INPUT_LEFT);
    InputManager::GetInstance().Add(KEY_INPUT_RIGHT);

    InputManager::GetInstance().Add(KEY_INPUT_TAB);

    InputManager::GetInstance().Add(KEY_INPUT_P);
    InputManager::GetInstance().Add(KEY_INPUT_Z);
    InputManager::GetInstance().Add(KEY_INPUT_X);
    InputManager::GetInstance().Add(KEY_INPUT_R);
    InputManager::GetInstance().Add(KEY_INPUT_E);
    InputManager::GetInstance().Add(KEY_INPUT_RETURN);
    InputManager::GetInstance().Add(KEY_INPUT_NUMPADENTER);
    InputManager::GetInstance().Add(KEY_INPUT_ESCAPE);

    InputManager::MouseInfo info;

    // 左クリック
    info = InputManager::MouseInfo();
    info.key = MOUSE_INPUT_LEFT;
    info.isKeyOld = false;
    info.isKeyNew = false;
    info.isTriggerDown = false;
    info.isTriggerUp = false;
    mouseInfos_.emplace(info.key, info);

    // 右クリック
    info = InputManager::MouseInfo();
    info.key = MOUSE_INPUT_RIGHT;
    info.isKeyOld = false;
    info.isKeyNew = false;
    info.isTriggerDown = false;
    info.isTriggerUp = false;
    mouseInfos_.emplace(info.key, info);
}

void InputManager::Update(void)
{
    // キーボード検知
    for (auto& keyPair : keyInfos_)
    {
        keyPair.second.isKeyOld = keyPair.second.isKeyNew;
        keyPair.second.isKeyNew = CheckHitKey(keyPair.second.key);

        keyPair.second.isTriggerDown =
            keyPair.second.isKeyNew && !keyPair.second.isKeyOld;

        keyPair.second.isTriggerUp =
            !keyPair.second.isKeyNew && keyPair.second.isKeyOld;
    }

    // マウス検知
    mouseInputState_ = GetMouseInput();
    GetMousePoint(&mousePosition_.x, &mousePosition_.y);

    for (auto& mousePair : mouseInfos_)
    {
        mousePair.second.isKeyOld = mousePair.second.isKeyNew;
        mousePair.second.isKeyNew = mouseInputState_ == mousePair.second.key;

        mousePair.second.isTriggerDown =
            mousePair.second.isKeyNew && !mousePair.second.isKeyOld;

        mousePair.second.isTriggerUp =
            !mousePair.second.isKeyNew && mousePair.second.isKeyOld;
    }

    // パッド情報
    SetJoypadInputState(JOYPAD_NUMBER::KEY_PAD1);
    SetJoypadInputState(JOYPAD_NUMBER::PAD1);
    SetJoypadInputState(JOYPAD_NUMBER::PAD2);
    SetJoypadInputState(JOYPAD_NUMBER::PAD3);
    SetJoypadInputState(JOYPAD_NUMBER::PAD4);
}

void InputManager::Destroy(void)
{
    keyInfos_.clear();
    mouseInfos_.clear();
    delete instance_;
}

void InputManager::Add(int key)
{
    InputManager::Info info = InputManager::Info();
    info.key = key;
    info.isKeyOld = false;
    info.isKeyNew = false;
    info.isTriggerDown = false;
    info.isTriggerUp = false;
    keyInfos_.emplace(key, info);
}

void InputManager::Clear(void)
{
    keyInfos_.clear();
}

bool InputManager::IsNew(int key) const
{
    return Find(key).isKeyNew;
}

bool InputManager::IsTriggerDown(int key) const
{
    return Find(key).isTriggerDown;
}

bool InputManager::IsTriggerUp(int key) const
{
    return Find(key).isTriggerUp;
}

Vector2 InputManager::GetMousePosition(void) const
{
    return mousePosition_;
}

int InputManager::GetMouseInputState(void) const
{
    return mouseInputState_;
}

bool InputManager::IsClickMouseLeft(void) const
{
    return mouseInputState_ == MOUSE_INPUT_LEFT;
}

bool InputManager::IsClickMouseRight(void) const
{
    return mouseInputState_ == MOUSE_INPUT_RIGHT;
}

bool InputManager::IsTriggerMouseLeft(void) const
{
    return FindMouse(MOUSE_INPUT_LEFT).isTriggerDown;
}

bool InputManager::IsTriggerMouseRight(void) const
{
    return FindMouse(MOUSE_INPUT_RIGHT).isTriggerDown;
}

InputManager::InputManager(void)
{
    mouseInputState_ = -1;
}

InputManager::InputManager(const InputManager& manager)
{
}

const InputManager::Info& InputManager::Find(int key) const
{
    auto iterator = keyInfos_.find(key);
    if (iterator != keyInfos_.end())
    {
        return iterator->second;
    }

    return emptyKeyInfo_;
}

const InputManager::MouseInfo& InputManager::FindMouse(int key) const
{
    auto iterator = mouseInfos_.find(key);
    if (iterator != mouseInfos_.end())
    {
        return iterator->second;
    }

    return emptyMouseInfo_;
}

InputManager::JOYPAD_TYPE InputManager::GetJoypadType(JOYPAD_NUMBER number)
{
    int numberIndex = static_cast<int>(number);
    return static_cast<InputManager::JOYPAD_TYPE>(::GetJoypadType(numberIndex));
}

DINPUT_JOYSTATE InputManager::GetJoypadDirectInputState(JOYPAD_NUMBER number)
{
    int numberIndex = static_cast<int>(number);
    ::GetJoypadDirectInputState(numberIndex, &directInputState_);
    return directInputState_;
}

XINPUT_STATE InputManager::GetJoypadXInputState(JOYPAD_NUMBER number)
{
    int numberIndex = static_cast<int>(number);
    ::GetJoypadXInputState(numberIndex, &xInputState_);
    return xInputState_;
}

void InputManager::SetJoypadInputState(JOYPAD_NUMBER number)
{
    int numberIndex = static_cast<int>(number);
    auto newState = GetJoypadInputState(number);
    auto& currentState = padInputStates_[numberIndex];

    const int MAX_BUTTONS = static_cast<int>(JOYPAD_BUTTON::MAX);

    for (int index = 0; index < MAX_BUTTONS; ++index)
    {
        currentState.buttonsOld[index] = currentState.buttonsNew[index];
        currentState.buttonsNew[index] = newState.buttonsNew[index];

        currentState.isOld[index] = currentState.isNew[index];

        // 0 より大きい場合に新たな入力とする
        const int THRESHOLD_ZERO = 0;
        currentState.isNew[index] = currentState.buttonsNew[index] > THRESHOLD_ZERO;

        currentState.isTriggerDown[index] =
            currentState.isNew[index] && !currentState.isOld[index];

        currentState.isTriggerUp[index] =
            !currentState.isNew[index] && currentState.isOld[index];

        currentState.analogKeyLeftX = newState.analogKeyLeftX;
        currentState.analogKeyLeftY = newState.analogKeyLeftY;
        currentState.analogKeyRightX = newState.analogKeyRightX;
        currentState.analogKeyRightY = newState.analogKeyRightY;
    }
}

InputManager::JOYPAD_INPUT_STATE InputManager::GetJoypadInputState(JOYPAD_NUMBER number)
{
    JOYPAD_INPUT_STATE resultState = JOYPAD_INPUT_STATE();
    auto type = GetJoypadType(number);

    switch (type)
    {
    case InputManager::JOYPAD_TYPE::OTHER:
        break;

    case InputManager::JOYPAD_TYPE::XBOX_360:
        break;

    case InputManager::JOYPAD_TYPE::XBOX_ONE:
    {
        auto directInput = GetJoypadDirectInputState(number);
        auto xInput = GetJoypadXInputState(number);

        int index;

        index = static_cast<int>(JOYPAD_BUTTON::TOP);
        resultState.buttonsNew[index] = directInput.Buttons[3]; // Y

        index = static_cast<int>(JOYPAD_BUTTON::LEFT);
        resultState.buttonsNew[index] = directInput.Buttons[2]; // X

        index = static_cast<int>(JOYPAD_BUTTON::RIGHT);
        resultState.buttonsNew[index] = directInput.Buttons[1]; // B

        index = static_cast<int>(JOYPAD_BUTTON::DOWN);
        resultState.buttonsNew[index] = directInput.Buttons[0]; // A

        index = static_cast<int>(JOYPAD_BUTTON::RIGHT_TRIGGER);
        resultState.buttonsNew[index] = xInput.RightTrigger;

        index = static_cast<int>(JOYPAD_BUTTON::LEFT_TRIGGER);
        resultState.buttonsNew[index] = xInput.LeftTrigger;

        index = static_cast<int>(JOYPAD_BUTTON::RIGHT_BUTTON);
        resultState.buttonsNew[index] = directInput.Buttons[5];

        index = static_cast<int>(JOYPAD_BUTTON::LEFT_BUTTON);
        resultState.buttonsNew[index] = directInput.Buttons[4];

        index = static_cast<int>(JOYPAD_BUTTON::START_BUTTON);
        resultState.buttonsNew[index] = directInput.Buttons[7];

        index = static_cast<int>(JOYPAD_BUTTON::SELECT_BUTTON);
        resultState.buttonsNew[index] = directInput.Buttons[6];

        // 左スティック
        resultState.analogKeyLeftX = directInput.X;
        resultState.analogKeyLeftY = directInput.Y;

        // 右スティック
        resultState.analogKeyRightX = directInput.Rx;
        resultState.analogKeyRightY = directInput.Ry;
    }
    break;

    case InputManager::JOYPAD_TYPE::DUAL_SHOCK_4:
        break;

    case InputManager::JOYPAD_TYPE::DUAL_SENSE:
    {
        auto directInput = GetJoypadDirectInputState(number);
        int index;

        index = static_cast<int>(JOYPAD_BUTTON::TOP);
        resultState.buttonsNew[index] = directInput.Buttons[3]; // △

        index = static_cast<int>(JOYPAD_BUTTON::LEFT);
        resultState.buttonsNew[index] = directInput.Buttons[0]; // □

        index = static_cast<int>(JOYPAD_BUTTON::RIGHT);
        resultState.buttonsNew[index] = directInput.Buttons[2]; // 〇

        index = static_cast<int>(JOYPAD_BUTTON::DOWN);
        resultState.buttonsNew[index] = directInput.Buttons[1]; // ×

        // 左スティック
        resultState.analogKeyLeftX = directInput.X;
        resultState.analogKeyLeftY = directInput.Y;

        // 右スティック
        resultState.analogKeyRightX = directInput.Z;
        resultState.analogKeyRightY = directInput.Rz;
    }
    break;

    case InputManager::JOYPAD_TYPE::SWITCH_JOY_CON_LEFT:
        break;

    case InputManager::JOYPAD_TYPE::SWITCH_JOY_CON_RIGHT:
        break;

    case InputManager::JOYPAD_TYPE::SWITCH_PRO_CONTROLLER:
        break;

    case InputManager::JOYPAD_TYPE::MAX:
        break;
    }

    return resultState;
}

bool InputManager::IsPadButtonNew(JOYPAD_NUMBER number, JOYPAD_BUTTON button) const
{
    int numberIndex = static_cast<int>(number);
    int buttonIndex = static_cast<int>(button);

    return padInputStates_[numberIndex].isNew[buttonIndex];
}

bool InputManager::IsPadButtonTriggerDown(JOYPAD_NUMBER number, JOYPAD_BUTTON button) const
{
    int numberIndex = static_cast<int>(number);
    int buttonIndex = static_cast<int>(button);

    return padInputStates_[numberIndex].isTriggerDown[buttonIndex];
}

bool InputManager::IsPadButtonTriggerUp(JOYPAD_NUMBER number, JOYPAD_BUTTON button) const
{
    int numberIndex = static_cast<int>(number);
    int buttonIndex = static_cast<int>(button);

    return padInputStates_[numberIndex].isTriggerUp[buttonIndex];
}