#!/bin/bash

### EDIT THESE VALUES #########################################################
APP="/usr/bin/spotify $@"
ICON="/usr/share/icons/hicolor/48x48/apps/spotify.png"
WAIT=2
###############################################################################

###############################################################################
### DON'T CHANGE ANYTHING BELOW
###############################################################################
function change-panel-icon {

    sleep $WAIT
    activeWinLine=$(xprop -root | grep "_NET_ACTIVE_WINDOW(WINDOW)")
    activeWinId="${activeWinLine:40}"

    xseticon -id "$activeWinId" "$ICON"
}

$APP & change-panel-icon
