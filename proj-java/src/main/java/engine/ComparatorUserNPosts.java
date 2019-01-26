package engine;

/**
 * Comparator pelo número de posts relevantes (tipo 1 ou tipo 2 )
 *
 */

import java.util.Comparator;

public class ComparatorUserNPosts implements Comparator<User>{
    public int compare(User u1, User u2){
        int n1,n2;
        n1 = u1.getCountPosts();
        n2 = u2.getCountPosts();
        if(n1 < n2) return 1;
        if(n1 > n2) return -1;
        else{
        	if(u1.getUserId() == u2.getUserId()) return 0;
        	if(u1.getUserId() > u2.getUserId()) return 1;
        	else return -1;
        }
    }
}