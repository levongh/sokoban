#pragma once

#include <QGLWidget>
#include <vector>
#include <utility>

struct Sokoban : QGLWidget
{
    enum class State
    {
        MENU,
        SELECT_LEVEL,
        PLAYER_STAT,
        PLAY,
        EXIT
        //ADD CREATE LEVEL
    };

    enum class Menu
    {
        START = -1,
        PLAY,
        SELECT_LEVEL,
        PLAYER_STAT,
        EXIT,
        END
    };

public:
    Sokoban(QWidget* parent = nullptr);

public:
    virtual void initializeGL() override;
    virtual void resizeGL(int, int) override;
    virtual void paintGL() override;

    virtual void keyReleaseEvent(QKeyEvent *event) override;

private:
    void processing();
    void draw();

    void drawMenu();
    void drawMenuSelectLevel();
    void drawPlayerStat();
    void drawPlay();

    void keyReleasedMenu(int);
    void keyReleasedMenuSelectLevel(int);
    void keyReleasedMenuPlayerStat(int);
    void keyReleasedPlay(int);

public:
    virtual ~Sokoban(){}

private:
    int m_selectLevelIndex;
    State m_state{State::MENU};
    Menu m_currentMenu{Menu::PLAY};

    std::vector<std::pair<Menu, std::string> > m_menu;
};
