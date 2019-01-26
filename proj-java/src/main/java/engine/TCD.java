package engine;

/**
 * Classe que contém a implementação da estrutura geral TCD
 *
 * @author Grupo 51
 */

import java.util.ArrayList;
import java.util.List;
import java.time.LocalDate;
import java.util.Set;
import java.util.Map;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Collections;
import java.util.TreeSet;

public class TCD{
    private PostBD posts;
    private UserBD users;
    private TagBD tags;

    /**
     * Construtor vazio
     */
    public TCD(){
        this.posts = new PostBD();
        this.users = new UserBD();
        this.tags = new TagBD();
    }
    
    /**
     * Contrutor parametizado
     * @param Map<Ineger,Post> posts
     * @param Map<Integer,User> users
     * @param Map<Integer,Tag> tags
     */
    public TCD (PostBD postsp, UserBD usersp, TagBD tagsp){
        this.posts = new PostBD(postsp);
        this.users = new UserBD(usersp);
        this.tags = new TagBD(tagsp);
    }

    /**
     * Contrutor por cópia
     * @param TCD TCD
     */
    public TCD(TCD community){
        this.posts = community.getPosts();
        this.users = community.getUsers();
        this.tags = community.getTags();
    }

    /**
     * Devolve o Map com todos os posts
     * @return Map<Integer,Post>
     */
    public PostBD getPosts(){
        return this.posts;
    }

    /**
     * Devolve o Map com todos os users
     * @return Map<Integer,User>
     */
    public UserBD getUsers(){
        return this.users;
    }

    /**
     * Devolve o Map com todos as tags
     * @return Map<Integer,Tag>
     */
    public TagBD getTags(){
        return this.tags;
    }
    
    public void clear(){
        this.posts.clear();
        this.users.clear();
        this.tags.clear();
    }
}

