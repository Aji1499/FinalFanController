package com.fancontroller;

import android.app.Activity;
import android.view.View;
import android.os.Bundle;
import android.util.Log;
import android.widget.Button;
import android.widget.TextView;
import android.widget.ToggleButton;
import android.widget.Toast;


import android.util.Log;



public class Fancontroller extends Activity {
    private static final String TOGGLE_TITLE_ON = "Turn Fan ON";
    private static final String TOGGLE_TITLE_OFF = "Turn Fan OFF";
    private FanSpeedClient fanSpeedClient;
    private TextView tvFanStatusAndSpeed;
    private ToggleButton toggleFan;
    private Button btnIncreaseSpeed;
    private Button btnDecreaseSpeed;
    private static final String TAG = "FanController_systemapp";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        tvFanStatusAndSpeed = findViewById(R.id.tv_fan_status_and_speed);
        toggleFan = findViewById(R.id.toggle_fan);
        btnIncreaseSpeed = findViewById(R.id.btn_increase_speed);
        btnDecreaseSpeed = findViewById(R.id.btn_decrease_speed);

        fanSpeedClient = new FanSpeedClient();

        // Initialize the UI with the current fan status and speed
        updateFanStatusAndSpeed();
        toggleFan.setChecked(fanSpeedClient.isFanOn());
        toggleFan.setText(fanSpeedClient.isFanOn() ? TOGGLE_TITLE_OFF : TOGGLE_TITLE_ON);

        toggleFan.setOnCheckedChangeListener((buttonView, isChecked) -> {
            if (isChecked) {
                if (fanSpeedClient.isFanOn()) {
                    Toast.makeText(Fancontroller.this, "Fan already ON", Toast.LENGTH_SHORT).show();
                    Log.d(TAG,"Fan already ON");
                } else {
                    fanSpeedClient.turnFanOn();
                    Toast.makeText(Fancontroller.this, "Fan turned ON", Toast.LENGTH_SHORT).show();
                    Log.d(TAG,"Fan turned ON");
                }
            } else {
                if (!fanSpeedClient.isFanOn()) {
                    Toast.makeText(Fancontroller.this, "Fan already OFF", Toast.LENGTH_SHORT).show();
                    Log.d(TAG,"Fan already OFF");
                } else {
                    fanSpeedClient.turnFanOff();
                    Toast.makeText(Fancontroller.this, "Fan turned OFF", Toast.LENGTH_SHORT).show();
                    Log.d(TAG,"Fan turned OFF");
                }
            }
            updateFanStatusAndSpeed();
        });

        btnIncreaseSpeed.setOnClickListener(v -> {
            if (fanSpeedClient.isFanOn()) {
                if (fanSpeedClient.getFanSpeed() == 5) {
                    Toast.makeText(Fancontroller.this, "Maximum speed reached", Toast.LENGTH_SHORT).show();
                    Log.d(TAG,"fan speed is maximum");
                } else {
                    fanSpeedClient.increaseFanSpeed();
                    updateFanStatusAndSpeed();
                }
            }
            else{
                Toast.makeText(Fancontroller.this, "Turn Fan ON first", Toast.LENGTH_SHORT).show();
                Log.d(TAG,"Turn Fan ON first");
            }
        });

        btnDecreaseSpeed.setOnClickListener(v -> {
            if (fanSpeedClient.isFanOn()) {
                if (fanSpeedClient.getFanSpeed() == 1) {
                    Toast.makeText(Fancontroller.this, "Minimum speed reached", Toast.LENGTH_SHORT).show();
                    Log.d(TAG,"fan speed is minimum");
                } else {
                    fanSpeedClient.decreaseFanSpeed();
                    updateFanStatusAndSpeed();
                }
            }
            else{
                Toast.makeText(Fancontroller.this, "Turn Fan ON first", Toast.LENGTH_SHORT).show();
                Log.d(TAG,"Turn Fan ON first");

            }

        });
    }

    private void updateFanStatusAndSpeed() {
        boolean fanOn = fanSpeedClient.isFanOn();
        int currentSpeed = fanSpeedClient.getFanSpeed();
        String fanStatusAndSpeed = "Fan Status: " + (fanOn ? "ON" : "OFF") + "  |  Current Speed: " + currentSpeed;
        tvFanStatusAndSpeed.setText(fanStatusAndSpeed);
        toggleFan.setText(fanOn ? TOGGLE_TITLE_OFF : TOGGLE_TITLE_ON);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        Log.i("FancontrollerApp", "Activity Destroyed");
    }
}
