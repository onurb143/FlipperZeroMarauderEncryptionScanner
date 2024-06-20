#include "../wifi_marauder_app_i.h"
#include "../script/wifi_marauder_script.h"

// Callback-funktion til redigering af en script-scene
static void wifi_marauder_scene_script_edit_callback(void* context, uint32_t index) {
    WifiMarauderApp* app = context;
    WifiMarauderScriptStage* current_stage = app->script->first_stage;
    uint32_t stage_index = 0;

    while(current_stage != NULL && stage_index < index) {
        current_stage = current_stage->next_stage;
        stage_index++;
    }
    app->script_edit_selected_stage = current_stage;

    if(app->script_edit_selected_stage != NULL) {
        scene_manager_set_scene_state(app->scene_manager, WifiMarauderSceneScriptEdit, index);
        scene_manager_next_scene(app->scene_manager, WifiMarauderSceneScriptStageEdit);
    }
}

// Callback-funktion til at tilføje en ny scene
static void wifi_marauder_scene_script_edit_add_callback(void* context, uint32_t index) {
    WifiMarauderApp* app = context;
    scene_manager_set_scene_state(app->scene_manager, WifiMarauderSceneScriptEdit, index);
    scene_manager_next_scene(app->scene_manager, WifiMarauderSceneScriptStageAdd);
}

// Hovedfunktion for at indlæse og vise script-scenens menu
void wifi_marauder_scene_script_edit_on_enter(void* context) {
    WifiMarauderApp* app = context;
    Submenu* submenu = app->submenu;
    WifiMarauderScript* script = app->script;
    submenu_set_header(submenu, script->name);

    WifiMarauderScriptStage* stage = script->first_stage;
    int stage_index = 0; // Add this line to initialize stage_index
    while(stage != NULL) {
        switch(stage->type) {
        case WifiMarauderScriptStageTypeScan: {
            WifiMarauderScriptStageScan* scan_stage = (WifiMarauderScriptStageScan*)stage->stage;
            char scan_info[128];

            // Format the scan stage information including encryption type
            snprintf(
                scan_info,
                sizeof(scan_info),
                "Scan: Type=%s, Channel=%d, Timeout=%d, Encryption=%d",
                scan_stage->type == WifiMarauderScriptScanTypeAp ? "ap" : "station",
                scan_stage->channel,
                scan_stage->timeout,
                scan_stage->encryption);
            submenu_add_item(
                submenu, scan_info, stage_index, wifi_marauder_scene_script_edit_callback, app);
            break;
        }
        case WifiMarauderScriptStageTypeSelect:
            submenu_add_item(
                submenu, "Select", stage_index, wifi_marauder_scene_script_edit_callback, app);
            break;
        case WifiMarauderScriptStageTypeDeauth:
            submenu_add_item(
                submenu, "Deauth", stage_index, wifi_marauder_scene_script_edit_callback, app);
            break;
        case WifiMarauderScriptStageTypeProbe:
            submenu_add_item(
                submenu, "Probe", stage_index, wifi_marauder_scene_script_edit_callback, app);
            break;
        case WifiMarauderScriptStageTypeSniffRaw:
            submenu_add_item(
                submenu, "Sniff raw", stage_index, wifi_marauder_scene_script_edit_callback, app);
            break;
        case WifiMarauderScriptStageTypeSniffBeacon:
            submenu_add_item(
                submenu,
                "Sniff beacon",
                stage_index,
                wifi_marauder_scene_script_edit_callback,
                app);
            break;
        case WifiMarauderScriptStageTypeSniffDeauth:
            submenu_add_item(
                submenu,
                "Sniff deauth",
                stage_index,
                wifi_marauder_scene_script_edit_callback,
                app);
            break;
        case WifiMarauderScriptStageTypeSniffEsp:
            submenu_add_item(
                submenu, "Sniff esp", stage_index, wifi_marauder_scene_script_edit_callback, app);
            break;
        case WifiMarauderScriptStageTypeSniffPmkid:
            submenu_add_item(
                submenu, "Sniff PMKID", stage_index, wifi_marauder_scene_script_edit_callback, app);
            break;
        case WifiMarauderScriptStageTypeSniffPwn:
            submenu_add_item(
                submenu, "Sniff pwn", stage_index, wifi_marauder_scene_script_edit_callback, app);
            break;
        case WifiMarauderScriptStageTypeBeaconList:
            submenu_add_item(
                submenu, "Beacon list", stage_index, wifi_marauder_scene_script_edit_callback, app);
            break;
        case WifiMarauderScriptStageTypeBeaconAp:
            submenu_add_item(
                submenu, "Beacon AP", stage_index, wifi_marauder_scene_script_edit_callback, app);
            break;
        case WifiMarauderScriptStageTypeExec:
            submenu_add_item(
                submenu,
                "Custom command",
                stage_index,
                wifi_marauder_scene_script_edit_callback,
                app);
            break;
        case WifiMarauderScriptStageTypeDelay:
            submenu_add_item(
                submenu, "Delay", stage_index, wifi_marauder_scene_script_edit_callback, app);
            break;
        default:
            break;
        }
        stage = stage->next_stage;
        stage_index++;
    }

    submenu_add_item(
        submenu, "[+] ADD STAGE", stage_index, wifi_marauder_scene_script_edit_add_callback, app);
    submenu_set_selected_item(
        submenu, scene_manager_get_scene_state(app->scene_manager, WifiMarauderSceneScriptEdit));
    view_dispatcher_switch_to_view(app->view_dispatcher, WifiMarauderAppViewSubmenu);
}

bool wifi_marauder_scene_script_edit_on_event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);
    return false;
}

void wifi_marauder_scene_script_edit_on_exit(void* context) {
    WifiMarauderApp* app = context;
    submenu_reset(app->submenu);
}
