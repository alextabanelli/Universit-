import models.Student;
import models.Continent;

public class Test {
    public static void main(String args[]) {
        Student s1 = new Student("Mario","Rossi",21,Continent.EUROPE,20,29.4);
        Student s2 = new Student("Joe","Smith",25,23.2);

        s1.getInfo();
        s2.getInfo();

        try {
            s1.setAvgGrade(25);
        } catch(Exception e) {  
            e.printStackTrace();
        }
    }
}
