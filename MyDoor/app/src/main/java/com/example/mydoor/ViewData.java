package com.example.mydoor;

import android.os.Bundle;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;


public class ViewData extends AppCompatActivity {
    private FirebaseDatabase mFirebaseDatabase;
    private DatabaseReference myRef;
    String ds="";

    @Override
    protected void onCreate(@Nullable  Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.viewstatus);
        mFirebaseDatabase=FirebaseDatabase.getInstance();
        myRef=mFirebaseDatabase.getReference();
        TextView d=(TextView)findViewById(R.id.textView);
        TextView c=(TextView)findViewById(R.id.textView2);
        myRef.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot snapshot) {
                String doorStatus=snapshot.child("Door").getValue().toString();
                if(doorStatus=="1") ds = "OPEN";
                else ds = "CLOSE";
                String counter=snapshot.child("Counter").getValue().toString();
                d.setText("Door Status: "+ds);
                c.setText("No. of people in room: "+counter);
            }

            @Override
            public void onCancelled( DatabaseError error) {
                Toast.makeText(getApplicationContext(),"Failed",Toast.LENGTH_SHORT).show();
            }
        });
    }
}
