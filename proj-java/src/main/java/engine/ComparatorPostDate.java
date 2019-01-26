package engine;

/**
 * Comparator pela data do Post
 *
 */

import java.util.Comparator;
import java.time.LocalDate;

public class ComparatorPostDate implements Comparator<Post>{
    public int compare(Post p1, Post p2){
        LocalDate d1,d2;
        d1 = p1.getPostDate();
        d2 = p2.getPostDate();  
        if(d1.isBefore(d2)) return 1;
        if(d1.isAfter(d2)) return -1;
        else{
            if(p1.getPostId() > p2.getPostId()) return 1;
            if(p1.getPostId() < p2.getPostId()) return -1;
            return 0;
        }
    }
}