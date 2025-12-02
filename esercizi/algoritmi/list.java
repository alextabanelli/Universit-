import models.IllegalExamsNumberException;
import models.IllegalGradeException;

public class Student extends Person {
    private int    exams;
    private double grade;

    public Student(String name, String surname) {
        super(name,surname);
        exams = 0;
        grade = 0;
    }

    public Student(String name, String surname, int exams, double grade) {
        super(name,surname);
        this.exams = exams;
        this.grade = grade;
    }

    public Student(String name, String surname, int age, Continent continent, int exams, double grade) {
        super(name,surname,age,continent);
        this.exams = exams;
        this.grade = grade;
    }

    public Student(String name, String surname, int age, Continent continent) {
        super(name,surname,age,continent);
        this.exams = 0;
        this.grade = 0;
    }


    public void setNumExams(int exams) throws IllegalExamsNumberException {
        if(exams < 0)
            throw new IllegalExamsNumberException("A student cannot have a negative number of exams");
        this.exams = exams;
    }

    public int getNumExams() {
        return this.exams;
    }

    public void setAvgGrade(double grade) throws IllegalGradeException {
        if(exams == 0 && grade != 0)
            throw new IllegalGradeException("The student cannot have a grade larger than zero with zero exams passed");
        else if(grade < 18 || grade > 30)
            throw new IllegalGradeException("The grade range is [18,30]");
        this.grade = grade;
    }

    public double getAvgGrade() {
        return this.grade;
    }

    @Override
    public void getInfo() {
        System.out.println(this);
    }

    @Override
    public String toString() {
        return super.toString() + ". I have done " + exams + " exams and my average grade is " + grade;        
    }
} 
