#include "PersonWindow.h"
#include "resource/StylesheetManager.h"
#include "city/Person.h"
#include "gui/Gui.h"
#include "gui/GuiText.h"
#include "gui/GuiImage.h"
#include "gui/GuiVBoxLayout.h"
#include "gui/GuiHBoxLayout.h"
#include "util/format.h"

PersonWindow::PersonWindow(StylesheetManager* stylesheetManager, const Person& person, int year) :
    GuiWindow(person.getFullName(), stylesheetManager->getStylesheet("window")),
    mStylesheetManager(stylesheetManager), mPerson(person), mYear(year), mImage(nullptr),
    mAgeText(nullptr), mWorkText(nullptr), mShortTermGoalText(nullptr), mLongTermGoalText(nullptr),
    mSleepText(nullptr), mHealthText(nullptr), mSafetyText(nullptr), mHungerText(nullptr), mHappinessText(nullptr)
{

}

PersonWindow::~PersonWindow()
{
    //dtor
}

void PersonWindow::setUp()
{
    // Zoom
    mRenderTexture.create(96, 96);
    sf::Sprite sprite(mRenderTexture.getTexture());
    mImage = mGui->createWithDefaultName<GuiImage>(sprite);

    // Personal info
    auto infoWidget = mGui->createWithDefaultName<GuiWidget>();
    auto firstNameText = mGui->createWithDefaultName<GuiText>("First name: " + mPerson.getFirstName(), 12, mStylesheetManager->getStylesheet("darkText"));
    auto lastNameText = mGui->createWithDefaultName<GuiText>("Last name: " + mPerson.getLastName(), 12, mStylesheetManager->getStylesheet("darkText"));
    mAgeText = mGui->createWithDefaultName<GuiText>("", 12, mStylesheetManager->getStylesheet("darkText"));
    mWorkText = mGui->createWithDefaultName<GuiText>("", 12, mStylesheetManager->getStylesheet("darkText"));
    mShortTermGoalText = mGui->createWithDefaultName<GuiText>("", 12, mStylesheetManager->getStylesheet("darkText"));
    mLongTermGoalText = mGui->createWithDefaultName<GuiText>("", 12, mStylesheetManager->getStylesheet("darkText"));
    infoWidget->add(firstNameText);
    infoWidget->add(lastNameText);
    infoWidget->add(mAgeText);
    infoWidget->add(mWorkText);
    infoWidget->add(mShortTermGoalText);
    infoWidget->add(mLongTermGoalText);
    infoWidget->setLayout(std::make_unique<GuiVBoxLayout>(3.0f));

    // Top widget
    auto topWidget = mGui->createWithDefaultName<GuiWidget>();
    topWidget->add(mImage);
    topWidget->add(infoWidget);
    topWidget->setLayout(std::make_unique<GuiHBoxLayout>(8.0f));

    // Bottom widget
    auto bottomWidget = mGui->createWithDefaultName<GuiWidget>();
    mSleepText = mGui->createWithDefaultName<GuiText>("", 12, mStylesheetManager->getStylesheet("darkText"));
    mHealthText = mGui->createWithDefaultName<GuiText>("", 12, mStylesheetManager->getStylesheet("darkText"));
    mSafetyText = mGui->createWithDefaultName<GuiText>("", 12, mStylesheetManager->getStylesheet("darkText"));
    mHungerText = mGui->createWithDefaultName<GuiText>("", 12, mStylesheetManager->getStylesheet("darkText"));
    mHappinessText = mGui->createWithDefaultName<GuiText>("", 12, mStylesheetManager->getStylesheet("darkText"));
    bottomWidget->add(mSleepText);
    bottomWidget->add(mHealthText);
    bottomWidget->add(mSafetyText);
    bottomWidget->add(mHungerText);
    bottomWidget->add(mHappinessText);
    bottomWidget->setLayout(std::make_unique<GuiVBoxLayout>(3.0f));

    // Window
    add(topWidget);
    add(bottomWidget);
    setPosition(sf::Vector2f(50.0f, 50.0f));
    setLayout(std::make_unique<GuiVBoxLayout>(8.0f, GuiLayout::Margins{8.0f, 8.0f, 8.0f, 8.0f}));
}

void PersonWindow::update()
{
    mAgeText->setString(format("Age: %d", mPerson.getAge(mYear)));
    mWorkText->setString("Work: " + mPerson.getWorkStatus());
    mShortTermGoalText->setString("Short term goal: " + mPerson.getShortTermBrain().toString());
    mLongTermGoalText->setString("Long term goal: " + mPerson.getLongTermBrain().toString());
    mSleepText->setString(format("Sleep: %.2f", mPerson.getSleep()));
    mHealthText->setString(format("Health: %.2f", mPerson.getHealth()));
    mSafetyText->setString(format("Safety: %.2f", mPerson.getSafety()));
    mHungerText->setString(format("Hunger: %.2f", mPerson.getHunger()));
    mHappinessText->setString(format("Happiness: %.2f", mPerson.getHappiness()));
}

void PersonWindow::onNewYear()
{
    ++mYear;
}

sf::RenderTexture& PersonWindow::getRenderTexture()
{
    return mRenderTexture;
}

sf::View PersonWindow::getView()
{
    sf::Vector2f center = mPerson.getCar().getKinematic().getPosition();
    return sf::View(center, sf::Vector2f(mRenderTexture.getSize()));
}
