import QtQuick 2.6
//import QtQuick.Controls 1.4
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

import Qt.labs.controls 1.0
import Qt.labs.controls.material 1.0
import Qt.labs.controls.universal 1.0
import Qt.labs.settings 1.0

import QtMultimedia 5.6

import Frumkin.FTimer 1.0


ApplicationWindow {
    id: root
    visible: true
    width: 400
    height: 720
    title: "Timer"
    readonly property  bool horizontalOriened: width > height

    GridLayout {
        id: mainLayout
        anchors.fill: parent
        anchors.margins: 20
        rowSpacing: height * 0.005
        columnSpacing: width * 0.008
        flow:  horizontalOriened ? GridLayout.LeftToRight : GridLayout.TopToBottom
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            //Layout.minimumHeight:
            //Layout.minimumWidth:
            color: "#5d5b59"
            //            Label {
            //                anchors.centerIn: parent
            //                text: "Top or left " + timer.msecsDisplay + " sec" + horizontalOriened
            //                color: "white"
            //            }
            ListView {
                id: timersView
                anchors.fill: parent
                orientation: ListView.Horizontal
                model:timersModel
                snapMode: ListView.SnapOneItem

                highlightRangeMode: ListView.StrictlyEnforceRange

                delegate: Text {
                    width: ListView.view.width
                    height: ListView.view.height

                    text: timersView.currentIndex === timer.currentTimerIndex ?
                              timer.msecsDisplay + " / " + timerSecs :
                              timerSecs + " / " + timerSecs

                    font.pointSize: 48
                }

                ListModel {
                    id: timersModel

                    function setModel() {
                        clear();
                        var timersCount = timer.timersCount();
                        //print(timersCount);
                        for (var i = 0; i < timersCount; i++) {
                            print(i);
                            append({"timerSecs": timer.getSecs(i)});
                        }
                    }
                }

            }
        }

        Rectangle {
            id: controls
            //Layout.fillWidth: true
            //Layout.fillHeight: true
            Layout.preferredHeight: horizontalOriened ?
                                        mainLayout.height :
                                        mainLayout.height * 0.1
            Layout.preferredWidth: horizontalOriened ?
                                       mainLayout.width * 0.1 :
                                       mainLayout.width
            Layout.minimumHeight: 80
            Layout.minimumWidth: 80
            color: "#1e1b18"

            Label {
                anchors.centerIn: parent
                text: "Bottom or right"
                color: "white"
            }
            MouseArea {
                anchors.fill: parent

                onClicked: {
                    //print("here1");
                    timer.start();
                    timersModel.setModel();
                    //startSound.play();
                    //print("here1");

                }
                FTimer {
                    id: timer
                    onStarted: startSound.play();
                    onCurrentTimerIndexChanged: {
                        print("onCurrentTimerIndexChanged");
                        timersView.currentIndex = currentTimerIndex;
                    }

                    Component.onCompleted: timersModel.setModel();
                }
                SoundEffect {
                    id: startSound
                    source: "./soundeffect.wav"
                }
            }
        }
    }
}
