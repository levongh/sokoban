#include <QKeyEvent>

#include "../include/sokoban.h"
#include "../include/settings.h"

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
    Settings::getInstance().load();
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
            renderText(static_cast<int>(x), static_cast<int>(y), m_menu[i].second.c_str(), fontSelected);
        } else {
            qglColor(Qt::white);
            renderText(static_cast<int>(x), static_cast<int>(y), m_menu[i].second.c_str(), font);
        }
        y += dy;
    }

}

void Sokoban::drawMenuSelectLevel()
{
    auto& settings = Settings::getInstance();
    static auto height = settings.screenHeight() / 3.f;
    static auto width = settings.getInstance().screenWidth() / 2.f;

    const std::vector<std::pair<unsigned, bool> >& levels = settings.getAvailableLevels();
    int lCount = static_cast<int>(levels.size());

    if (levels.empty()) {
        return;
    }
    static auto font = QFont("Comic Sans MS", 15);
    static auto fontSelected = QFont("Comic Sans MS", 20);
    fontSelected.setBold(true);

    int tmp = (m_selectLevelIndex - 6);
    int start = tmp < 0 ? 0 : tmp;

    tmp = start + 6;
    int end = (tmp < lCount) ? tmp : lCount - 1;

    auto x = width - 100;
    auto y = height;
    auto dy = 25.f;

    for (int i = start; i <= end; ++i) {
        const auto& lvl = levels[i].first;
        const auto& isLock = levels[i].second;
        //const auto& [lvl, isLock] = levels[i];

        QString item = "level " + QString::number(lvl);
        QFont& rf = (i == m_selectLevelIndex) ? fontSelected : font;

        Qt::GlobalColor color = Qt::gray;
        if (i == m_selectLevelIndex) {
            if (isLock == true)
                color = Qt::red;
        } else {
            if (isLock == true)
                color = Qt::white;
        }
        qglColor(color);
        renderText(static_cast<int>(x), static_cast<int>(y), item, rf);
        y += dy;
    }
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
    const auto levels = Settings::getInstance().getAvailableLevels();
    int levelsCount = static_cast<int>(levels.size());

    switch (key) {
    case Qt::Key_Up:
        --m_selectLevelIndex;
        if (m_selectLevelIndex < 0) {
            m_selectLevelIndex = 0;
        }
        break;
    case Qt::Key_Down:
        ++m_selectLevelIndex;
        if(m_selectLevelIndex >= levelsCount) {
            m_selectLevelIndex = levelsCount - 1;
        }
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
