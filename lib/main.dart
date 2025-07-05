import 'package:flutter/material.dart';
import 'package:zego_uikit_prebuilt_call/zego_uikit_prebuilt_call.dart';
import 'dart:async';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: CallPage(
        userID: 'user1', // change ça pour chaque appareil
        userName: 'User 1',
      ),
    );
  }
}

class CallPage extends StatelessWidget {
  final String userID;
  final String userName;

  const CallPage({super.key, required this.userID, required this.userName});

  @override
  Widget build(BuildContext context) {
    return ZegoUIKitPrebuiltCall(
      appID: 925144029, // Remplace avec ton appID
      appSign:
          "b2fa018858c607b8b3b64bb2ba972130e9cb0310afc7e7bd6575e46a45af2325", // Ton appSign
      userID: userID,
      userName: userName,
      callID: "test-room", // Doit être identique sur les deux devices
      config: ZegoUIKitPrebuiltCallConfig.oneOnOneVideoCall(),
    );
  }
}
