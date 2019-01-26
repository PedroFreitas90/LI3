package engine;

/**
 * Comparator pelo número de respostas
 *
 */

import java.util.Comparator;
import java.time.LocalDate;

public class ComparatorPostNRes implements Comparator<Post>{
    public int compare(Post p1, Post p2){
        int res1,res2;
        res1 = p1.getPostNRes();
        res2 = p2.getPostNRes();	
        if(res1 == res2) return 1;
        if(res1 > res2) return -1;
        else return 1;
    }
}