package com.rightware.kanzi.datasourcetesttoolclient;

import android.content.res.Configuration;
import android.os.Bundle;
import android.support.v4.app.FragmentActivity;
import android.view.WindowManager;

import com.rightware.kanzi.KanziView;

public class DataSourceTestToolClient extends FragmentActivity
{
    private static final String TAG = "DataSourceTestToolClient";
    private KanziView mView = null;

    @Override
    protected void onCreate(Bundle icicle)
    {
        setContentView(R.layout.main);

        mView = findViewById(R.id.kanzicontent);
        mView.registerLifecycle(getLifecycle());

        // Force the screen to stay on when this app is on front (no need to clear).
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

        super.onCreate(icicle);
    }

    @Override
    public void onConfigurationChanged(Configuration newConfig)
    {
        super.onConfigurationChanged(newConfig);

        mView.setOrientation(newConfig.orientation);
    }
}
