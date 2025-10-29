final float x0 = 0, y0 = 0, z0 = 20, m0 = 20;
final float l1 = 100, l2 = 100, l3 = 100, l4 = 100;
float angle = 0, x = 700, y = 700, z = 700;
float m1 = m0, z1 = z0 + l1;
float a1, a2, a3, a4;
float m4, m3, z3, x3, y3, mt, b1, b2, m2, z2;

// angle is changed with up and down errors

void setup() {
    size(1000, 500);
    frameRate(60);
}

void draw() {
    background(255);

    if (mousePressed) {
        m4 = mouseX;
        z = height - mouseY;
    }

    a1 = degrees(atan2(y - y0, x - x0));

    m3 = m4 - l4 * cos(radians(angle));
    z3 = z - l4 * cos(radians(90 - angle));
    x3 = x0 + m3 * cos(radians(a1));
    y3 = y0 + m3 * sin(radians(a1));

    mt = sqrt(sq(z3 - z1) + sq(m3 - m1));

    if (mt > l2 + l3 || mt < abs(l2 - l3)) {
        println("Failed calculating. Cannot reach the point");
        return;
    }

    a3 = 180 - degrees(acos((l2 * l2 + l3 * l3 - mt * mt) / (2 * l2 * l3)));
    
    b1 = degrees(atan2(m3 - m1, z3 - z1));
    b2 = degrees(acos((l2 * l2 + mt * mt - l3 * l3) / (2 * l2 * mt)));
    
    print("b1 and b2:");
    print(b1);
    print(" and ");
    println(b2);
    
    a2 = b1 + b2;
    a4 = angle + a2 + a3 - 90;

    print("a1 = "); print(a1);
    print("; a2 = "); print(a2);
    print("; a3 = "); print(a3);
    print("; a4 = "); println(a4);

    m2 = m1 + l2 * sin(radians(a2));
    z2 = z1 + l2 * cos(radians(a2));

    line(m0, height - z0, m1, height - z1);
    line(m1, height - z1, m2, height - z2);
    line(m2, height - z2, m3, height - z3);
    line(m3, height - z3, m4, height - z);
}

void keyPressed() {
    if (keyCode == UP) {
        angle++;
        delay(5);
        return;
    }

    if (keyCode == DOWN) {
        angle--;
        delay(5);
    }
    
    if(key == 'q') {
        noLoop();
        exit();
    }
}
