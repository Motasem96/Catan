cmake_minimum_required(VERSION 3.12)
project(SIEDLER_VON_CATAN)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5.1 COMPONENTS network audio graphics window system REQUIRED)
add_executable(game
    src/main.cpp
    src/helpers/StateManager/StateManager.cpp
    src/helpers/AssetManager/AssetManager.cpp
    src/helpers/InputManager/InputManager.cpp
    src/Game/Game.cpp
    src/States/StartMenuState/StartMenuState.cpp
    src/components/Button/Button.cpp
    src/components/Display/Display.cpp
    src/States/GameState/GameState.cpp
    src/components/Field/Field.cpp
    src/components/Chip/Chip.cpp
    src/components/BankCards/RawMaterial/RawMaterial.cpp
    src/components/BankCards/TrendCard/TrendCard.cpp
    src/components/Dice/Dice.cpp
    src/States/AddPlayerState/AddPlayerState.cpp
    src/components/TextBox/TextBox.cpp
    src/Player/Player.cpp
    src/components/GameFigure/GameFigure.cpp
    src/actions/ActionMachine/ActionMachine.cpp
    src/actions/ShowDiceRolls/ShowDiceRolls.cpp
    src/actions/ShowPlayerOptions/ShowPlayerOptions.cpp
    src/actions/PassToNextPlayer/PassToNextPlayer.cpp
    src/actions/BuildGameFigure/BuildGameFigure.cpp
    src/actions/ChooseSprite/ChooseSprite.cpp
    src/actions/ChooseCorner/ChooseCorner.cpp
)
target_link_libraries(game sfml-window sfml-graphics sfml-audio sfml-network)