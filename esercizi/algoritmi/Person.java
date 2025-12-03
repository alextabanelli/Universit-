public class Person {
    private final String name;
    private final String surname;
    private int age;
    private Continent continent;    

    public Person(String name, String surname, int age, Continent continent) {
        this.name      = name;
        this.surname   = surname;
        this.age       = age;
        this.continent = continent;
    }

    public Person(String name, String surname) {
        this.name      = name;
        this.surname   = surname;
        this.age       = 0;
        this.continent = Continent.UNKNOWN;
    }

    public void setAge(int age) {
        if(age >= 0 && age <= 130)
            this.age = age;
    }

    public void setContinent(Continent continent) {
        this.continent = continent;
    }

    public String getName() {
        return name;
    }
    
    public String getSurname() {
        return surname;
    }
    
    public int getAge() {
        return age;
    }

    public Continent getContinent() {
        return continent;
    }

    public void getInfo() {
        System.out.println(this);
    }

    @Override
    public String toString() {
        return "My name is " + name + " " + surname + ". I am " + age + " years old and I live in " + continent;   
    }
}
