### This file is automatically generated by Qt Design Studio.
### Do not change

#---------- Add backgrounds
set(BACKGROUNDS_DIR "images/gameBackgrounds")
file(GLOB PNG_BACKGROUNDS "${BACKGROUNDS_DIR}/*.png")
set(PNG_BACKGROUNDS_RESOURCES "")
foreach(PNG_FILE ${PNG_BACKGROUNDS})
    get_filename_component(PNG_NAME ${PNG_FILE} NAME)
    set(PNG_RESOURCE "images/gameBackgrounds/${PNG_NAME}")
    list(APPEND PNG_BACKGROUNDS_RESOURCES ${PNG_RESOURCE})
endforeach()
#--------- Add icons

set(ICONS_DIR "images/icons")
file(GLOB PNG_ICONS "${ICONS_DIR}/*.png")
set(PNG_ICONS_RESOURCES "")
foreach(PNG_FILE ${PNG_ICONS})
    get_filename_component(PNG_NAME ${PNG_FILE} NAME)
    set(PNG_RESOURCE "images/icons/${PNG_NAME}")
    list(APPEND PNG_ICONS_RESOURCES ${PNG_RESOURCE})
endforeach()
#--------- Add gifs

set(ICONS_GIF_DIR "images/icons")
file(GLOB GIF_ICONS "${ICONS_GIF_DIR}/*.gif")
set(GIF_ICONS_RESOURCES "")
foreach(GIF_FILE ${GIF_ICONS})
    get_filename_component(GIF_NAME ${GIF_FILE} NAME)
    set(GIF_RESOURCE "images/icons/${GIF_NAME}")
    list(APPEND GIF_ICONS_RESOURCES ${GIF_RESOURCE})
endforeach()
#--------- Qml Files 

set(QML_DIR "qml")
file(GLOB QML_FILES "${QML_DIR}/*.qml")
set(QML_RESOURCES "")
foreach(QML_FILE ${QML_FILES})
    get_filename_component(QML_NAME ${QML_FILE} NAME)
    set(QML_RESOURCE "qml/${QML_NAME}")
    list(APPEND QML_RESOURCES ${QML_RESOURCE})
endforeach()

#--------- modsList modules

set(QML_MLDIR "qml/modsList")
file(GLOB QML_MLFILES "${QML_MLDIR}/*.qml")
set(QML_MLRESOURCES "")
foreach(QML_MLFILE ${QML_MLFILES})
    get_filename_component(QML_MLNAME ${QML_MLFILE} NAME)
    set(QML_MLRESOURCE "qml/modsList/${QML_MLNAME}")
    list(APPEND QML_MLRESOURCES ${QML_MLRESOURCE})
endforeach()
#--------- bottommenu
set(QML_BMDIR "qml/bottomMenu")
file(GLOB QML_BMFILES "${QML_BMDIR}/*.qml")
set(QML_BMRESOURCES "")
foreach(QML_BMFILE ${QML_BMFILES})
    get_filename_component(QML_BMNAME ${QML_BMFILE} NAME)
    set(QML_BMRESOURCE "qml/bottomMenu/${QML_BMNAME}")
    list(APPEND QML_BMRESOURCES ${QML_BMRESOURCE})
endforeach()

#--------- customQmlModules
set(QML_CMDIR "qml/customModules")
file(GLOB QML_CMFILES "${QML_CMDIR}/*.qml")
set(QML_CMRESOURCES "")
foreach(QML_CMFILE ${QML_CMFILES})
    get_filename_component(QML_CMNAME ${QML_CMFILE} NAME)
    set(QML_CMRESOURCE "qml/customModules/${QML_CMNAME}")
    list(APPEND QML_CMRESOURCES ${QML_CMRESOURCE})
endforeach()
#--------------------------------------
qt_add_library(content STATIC)

qt6_add_qml_module(content
    URI "content"
    VERSION 1.0
    QML_FILES
        ${QML_RESOURCES}
        ${QML_MLRESOURCES}
        ${QML_CMRESOURCES}
        ${QML_BMRESOURCES}
    RESOURCES
        fonts/fonts.txt

        ${PNG_BACKGROUNDS_RESOURCES}
        ${PNG_ICONS_RESOURCES}
        ${GIF_ICONS_RESOURCES}
    )

#qt_add_library(customModules STATIC)
#qt6_add_qml_module(customModules
#    URI "customModules"
#    VERSION 1.0
#    QML_FILES
#        ${QML_CMRESOURCES}
#    OUTPUT_DIRECTORY qml/customModules
#    )
