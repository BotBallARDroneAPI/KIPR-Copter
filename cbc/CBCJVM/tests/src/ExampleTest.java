// Stolen from: http://www.mkyong.com/unittest/testng-tutorial-1-basic-usage/

import java.util.*;
import org.testng.Assert;
import org.testng.annotations.*;
 
public class ExampleTest {
 
    private Collection<String> collection;
 
    @BeforeClass
    public void oneTimeSetUp() {
        // one-time initialization code   
    	//System.out.println("@BeforeClass - oneTimeSetUp");
    }
 
    @AfterClass
    public void oneTimeTearDown() {
        // one-time cleanup code
    	//System.out.println("@AfterClass - oneTimeTearDown");
    }
 
    @BeforeMethod
    public void setUp() {
        collection = new ArrayList<String>();
        //System.out.println("@BeforeMethod - setUp");
    }
 
    @AfterMethod
    public void tearDown() {
        collection.clear();
        //System.out.println("@AfterMethod - tearDown");
    }
 
    @Test
    public void testEmptyCollection() {
        Assert.assertEquals(collection.isEmpty(),true);
        //System.out.println("@Test - testEmptyCollection");
    }
 
    @Test
    public void testOneItemCollection() {
        collection.add("itemA");
        Assert.assertEquals(collection.size(),1);
        //System.out.println("@Test - testOneItemCollection");
    }
}
