#pragma once

#include "message/Mailbox.h"
#include "gui/GuiWindow.h"

class MessageBus;
class StylesheetManager;
class GuiButton;
class GuiTabWidget;

class PoliciesWindow : public GuiWindow
{
public:
    PoliciesWindow(MessageBus* messageBus, StylesheetManager* stylesheetManager);
    ~PoliciesWindow();

    virtual void setUp() override;

    void update();

private:
    StylesheetManager* mStylesheetManager;
    Mailbox mMailbox;
    GuiWidget* mTabButtonsWidget;
    std::vector<GuiButton*> mTabButtons;
    GuiTabWidget* mTabWidget;

    void createLine(GuiWidget* tab, const std::string& label, const std::string& value,
        const std::string& regex, const std::string& suffix = "");
    void updateTab(std::size_t tab);
};
