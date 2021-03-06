package com.example.akshay.sample;

import android.os.Bundle;
import android.os.Handler;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.jjoe64.graphview.GraphView;
import com.jjoe64.graphview.series.DataPoint;
import com.jjoe64.graphview.series.LineGraphSeries;

import java.util.Random;

public class moist extends Fragment{

    private LineGraphSeries<DataPoint> mSeries1;
    private LineGraphSeries<DataPoint> mSeries2;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View rootView = inflater.inflate(R.layout.humidity, container, false);
        GraphView graph = rootView.findViewById(R.id.hgv);
        mSeries1 = new LineGraphSeries<>(generateData());
        graph.addSeries(mSeries1);
        graph.getLegendRenderer();
        graph.getViewport().setXAxisBoundsManual(true);
        graph.getViewport().setMinX(0);
        graph.getViewport().setMaxX(12);
        graph.getViewport().setYAxisBoundsManual(true);
        graph.getViewport().setMinY(8);
        graph.getViewport().setMaxY(25);

        return rootView;
    }

    private DataPoint[] generateData() {
        int count = 23;
        DataPoint[] values = new DataPoint[count];
        for (int i=0; i<count; i++) {
            double x = i;
            double y = (Math.random() * ( 17 )) + 8;
            DataPoint v = new DataPoint(x, y);
            values[i] = v;
        }
        return values;
    }

    Random mRand = new Random();
}
