package engine;

/**
 * Comparator pela data do Post
 *
 */

import java.util.Comparator;
import java.time.LocalDate;

public class ComparatorPostScore implements Comparator<Post>{
    public int compare(Post p1, Post p2){
        int s1, s2;
        s1 = p1.getPostScore();
        s2 = p2.getPostScore();	
        if(s1 == s2) return 1;
        if(s1>s2) return -1;
        else return 1;
    }
}