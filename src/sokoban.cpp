#include <QKeyEvent>

#include "include/sokoban.h"
#include "include/settings.h"

Sokoban::State menuToState(const Sokoban::Menu& menu)
{
    switch (menu) {
    case Sokoban::Menu::START:
    case Sokoban::Menu::END:
        return Sokoban::State::MENU;
    case Sokoban::Menu::SELECT_LEVEL:
        return Sokoban::State::SELECT_LEVEL;
    case Sokoban::Menu::PLAY:
        return Sokoban::State::PLAY;
    case Sokoban::Menu::PLAYER_STAT:
        return Sokoban::State::PLAYER_STAT;
    case Sokoban::Menu::EXIT:
        return Sokoban::State::EXIT;
    }
}

Sokoban::Menu operator++ (Sokoban::Menu& menu)
{
    menu = Sokoban::Menu(static_cast<int>(menu) + 1);
    if (menu == Sokoban::Menu::END) {
        menu = Sokoban::Menu::PLAY;
    }
    return menu;
}

Sokoban::Menu operator-- (Sokoban::Menu& menu)
{
    menu = Sokoban::Menu(static_cast<int>(menu) - 1);
    if (menu == Sokoban::Menu::START) {
        menu = Sokoban::Menu::EXIT;
    }
    return menu;
}

Sokoban::Sokoban(QWidget* parent)
    : QGLWidget(parent)
{
    m_menu.push_back(std::make_pair<Menu, std::string>(Menu::PLAY, "Play"));
    m_menu.push_back(std::make_pair<Menu, std::string>(Menu::SELECT_LEVEL, "Select level"));
    m_menu.push_back(std::make_pair<Menu, std::string>(Menu::PLAYER_STAT, "Statistics"));
    m_menu.push_back(std::make_pair<Menu, std::string>(Menu::EXIT, "Exit"));
}

void Sokoban::initializeGL()
{
    static auto height = Settings::getInstance().screenHeight();
    static auto width = Settings::getInstance().screenWidth();
    glOrtho(0, width, height, 0, 0, 1);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_POINT_SMOOTH);
    glDisable(GL_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
}

void Sokoban::resizeGL(int width, int height)
{
    static auto h = Settings::getInstance().screenHeight();
    static auto w = Settings::getInstance().screenWidth();
    glLoadIdentity();
    glViewport(0, 0, static_cast<GLint>(width), static_cast<GLint>(height));
    glOrtho(0, w, h, 0, 0, 1);
}

void Sokoban::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 139, 139, 0);

    processing();
    draw();
}

void Sokoban::keyReleaseEvent(QKeyEvent *event)
{
//    if (event->key() == Qt::Key_Escape) {
//        close();
//    }
    switch (m_state) {
    case State::MENU:
        keyReleasedMenu(event->key());
        break;
    case State::SELECT_LEVEL:
        keyReleasedMenuSelectLevel(event->key());
        break;
    case State::PLAYER_STAT:
        keyReleasedMenuPlayerStat(event->key());
        break;
    case State::PLAY:
        keyReleasedPlay(event->key());
        break;
    case State::EXIT:
        close();
        break;
    }
}

void Sokoban::processing()
{
    switch (m_state) {
    case State::MENU:
        break;
    case State::SELECT_LEVEL:
        break;
    case State::PLAYER_STAT:
        break;
    case State::PLAY:
        break;
    case State::EXIT:
        close();
        break;
    }
}

void Sokoban::draw()
{
    switch (m_state) {
    case State::MENU:
        drawMenu();
        break;
    case State::SELECT_LEVEL:
        drawMenuSelectLevel();
        break;
    case State::PLAYER_STAT:
        drawPlayerStat();
        break;
    case State::PLAY:
        drawPlay();
        break;
    case State::EXIT:
        close();
        break;
    }
}

void Sokoban::drawMenu()
{
    static auto height = Settings::getInstance().screenHeight() / 3.f;
    static auto width = Settings::getInstance().screenWidth() / 2.f;

    static auto font = QFont("Sans", 25);
    static auto fontSelected= QFont("Sans", 30);
    fontSelected.setBold(true);

    auto x = width - 100;
    auto y = height;
    auto dy = 55.f;

    for (size_t i = 0; i < m_menu.size(); ++i) {
        if (i == static_cast<size_t>(m_currentMenu)) {
            qglColor(Qt::red);
            renderText(x, y, m_menu[i].second.c_str(), fontSelected);
        } else {
            qglColor(Qt::white);
            renderText(x, y, m_menu[i].second.c_str(), font);
        }
        y += dy;
    }

}

void Sokoban::drawMenuSelectLevel()
{

}

void Sokoban::drawPlayerStat()
{

}

void Sokoban::drawPlay()
{

}

void Sokoban::keyReleasedMenu(int key)
{
    switch (key) {
    case Qt::Key_Up:
        --m_currentMenu;
        break;
    case Qt::Key_Down:
        ++m_currentMenu;
        break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
        m_state = menuToState(m_currentMenu);
        break;
    }
    updateGL();
}

void Sokoban::keyReleasedMenuSelectLevel(int key)
{
    switch (key) {
    case Qt::Key_Up:
        break;
    case Qt::Key_Down:
        break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
        break;
    case Qt::Key_Escape:
        m_state = State::MENU;
        break;
    }
    updateGL();
}

void Sokoban::keyReleasedMenuPlayerStat(int key)
{
    switch (key) {
    case Qt::Key_Up:
        break;
    case Qt::Key_Down:
        break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
        break;
    case Qt::Key_Escape:
        m_state = State::MENU;
        break;
    }
    updateGL();
}

void Sokoban::keyReleasedPlay(int key)
{
    switch (key) {
    case Qt::Key_Up:
        break;
    case Qt::Key_Down:
        break;
    case Qt::Key_Left:
        break;
    case Qt::Key_Right:
        break;
    case Qt::Key_Escape:
        m_state = State::MENU;
        break;
    case Qt::Key_R:
        break;
    }
    updateGL();
}
