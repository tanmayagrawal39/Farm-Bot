package com.example.akshay.sample;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.ImageView;

import com.bumptech.glide.Glide;import com.firebase.ui.storage.images.FirebaseImageLoader;
import com.google.firebase.storage.FirebaseStorage;
import com.google.firebase.storage.StorageReference;

public class images extends AppCompatActivity {

    private FirebaseStorage storage;
    private StorageReference  storageReference;

    private ImageView imageView ;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_images);
        imageView = findViewById(R.id.image);
        storage = FirebaseStorage.getInstance();
        storageReference = storage.getReference().child("images/example1.jpg");
        Glide.with(this).using(new FirebaseImageLoader()).load(storageReference).into(imageView);
    }
}
