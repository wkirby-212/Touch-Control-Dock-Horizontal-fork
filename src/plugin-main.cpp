#include <obs-module.h>
#include <obs-frontend-api.h>

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("touch-control-dock", "en-US")

static QWidget *g_helpWidget = nullptr;

const char *obs_module_name(void)
{
    return "Touch Control Dock";
}

bool obs_module_load(void)
{
    g_helpWidget = new QWidget();
    auto *layout = new QVBoxLayout(g_helpWidget);

    auto *label = new QLabel(
        "Touch Control Dock loaded.\n\n"
        "This package includes a touch-first HTML control surface.\n"
        "Load it as an OBS Browser Dock:\n"
        "  data/touch-ui/index.html\n\n"
        "This native dock is only a lightweight confirmation/help panel."
    );

    label->setWordWrap(true);
    layout->addWidget(label);

    obs_frontend_add_dock_by_id(
        "touch.control.help",
        "Touch Control Help",
        g_helpWidget
    );

    blog(LOG_INFO, "[Touch Control Dock] Loaded.");
    return true;
}

void obs_module_unload(void)
{
    obs_frontend_remove_dock("touch.control.help");

    delete g_helpWidget;
    g_helpWidget = nullptr;

    blog(LOG_INFO, "[Touch Control Dock] Unloaded.");
}
