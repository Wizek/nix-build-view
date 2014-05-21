#include "HelpWidget.hpp"

int HelpWidget::type() {
    return WidgetName::HelpWidget;
}

AdvancedStringContainer HelpWidget::render(unsigned int width, unsigned int height) {
    //copy the last h elements from terminal to the out buffer
    AdvancedStringContainer out;

    AdvancedStringContainer s;
    s << AdvancedString("nix-build-view $version (c) 2014++ Joachim Schiele\n", COLOR_CYAN);
    s << AdvancedString("Released under the GNU GPL v3\n", COLOR_CYAN);
    s << "\n";
    s << "\n";
    s << "     " << "keyboard shortcuts: \n";
    s << "\n";
    s << "         " << AdvancedString("q", COLOR_CYAN) << " - quit the program\n";
    s << "\n";
    s << "         " << AdvancedString("h", COLOR_CYAN) << " - help\n";
    s << "         " << AdvancedString("1", COLOR_CYAN) << " - combined view with log+fetch+build\n";
    s << "         " << AdvancedString("2", COLOR_CYAN) << " - shows the logfile output of nix-build-view\n";
    s << "         " << AdvancedString("3", COLOR_CYAN) << " - shows the download widget (can be scrolled)\n";
    s << "         " << AdvancedString("4", COLOR_CYAN) << " - shows the build widget (can be scrolled)\n";
    s << "\n";
    s << "         " << AdvancedString("up", COLOR_CYAN) << " - scrolls view up\n";
    s << "         " << AdvancedString("down", COLOR_CYAN) << " - scrolls the view down\n";
    s << "         " << AdvancedString("page up", COLOR_CYAN) << " - scrolls view up by several lines\n";
    s << "         " << AdvancedString("page down", COLOR_CYAN) << " - scrolls view down by several lines\n";
    s << "         " << AdvancedString("pos1", COLOR_CYAN) << " - scrolls view to beginning\n";
    s << "         " << AdvancedString("end", COLOR_CYAN) << " - scrolls view to end\n";

    //caches the output for better performance
    if ((m_width != width) || (m_height != height)) {
        m_width = width;
        m_height = height;
        AdvancedStringContainer::terminal_rasterize(m_terminal, s, width);
    }

    std::vector<AdvancedStringContainer>::const_iterator it_b = m_terminal.begin();
    std::vector<AdvancedStringContainer>::const_iterator it_e = m_terminal.end();

    int m_line = 0;

    if (it_e - height - m_line >= it_b)
        it_b = it_e - height - m_line;

    for(unsigned int i=0; i < height; ++i) {
        if (it_b >= it_e)
            break;
        AdvancedStringContainer t = *it_b++;
        out << t;
    }

    return out;
}
