import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.2

import hubbatov.jarvis 1.0

Window {
	visible: true
	width: 640
	height: 480
	title: qsTr("Jarvis 0.0")

    Jarvis{
        id: __jarvis
	}

	Text {
		id: __debigPanel

		anchors.centerIn: parent
	}

}
