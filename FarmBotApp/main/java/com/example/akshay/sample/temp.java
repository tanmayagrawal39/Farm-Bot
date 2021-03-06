package com.example.akshay.sample;

import android.os.Handler;
import android.support.v4.app.Fragment;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.jjoe64.graphview.GraphView;
import com.jjoe64.graphview.series.DataPoint;
import com.jjoe64.graphview.series.LineGraphSeries;

import java.util.Random;

public class temp extends Fragment {

    private final Handler mHandler = new Handler();
    private Runnable mTimer1;
    private Runnable mTimer2;
    private LineGraphSeries<DataPoint> mSeries1;
    private LineGraphSeries<DataPoint> mSeries2;
    private double graph2LastXValue = 5d;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View rootView = inflater.inflate(R.layout.humidity, container, false);
        GraphView graph = (GraphView) rootView.findViewById(R.id.hgv);
        mSeries1 = new LineGraphSeries<>(generateData());
        graph.getLegendRenderer();
        graph.getViewport().setXAxisBoundsManual(true);
        graph.getViewport().setMinX(0);
        graph.getViewport().setMaxX(12);
        graph.getViewport().setYAxisBoundsManual(true);
        graph.getViewport().setMinY(25);
        graph.getViewport().setMaxY(40);
        graph.addSeries(mSeries1);

        return rootView;
    }

    private DataPoint[] generateData() {
        int count = 23;
        DataPoint[] values = new DataPoint[count];
        for (int i=0; i<count; i++) {
            double x = i;
            double y = (Math.random() * ( 15 )) + 25;
            DataPoint v = new DataPoint(x, y);
            values[i] = v;
        }
        return values;
    }

    Random mRand = new Random();
}

