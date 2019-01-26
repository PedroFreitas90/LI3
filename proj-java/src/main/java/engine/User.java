package engine;

/**
 * Classe que contém a implementação da estrutura dos Users
 *
 * @author Grupo 51
 */

import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import java.time.LocalDate;

public class User {
    private long id;
    private int reputacao;
    private String nome;
    private String bio;
    private int nposts;
    private ArrayList<Post> uposts;

    /**
     * Construtor vazio
     */
    public User(){
        this.id = -2;
        this.reputacao = 0;
        this.nome = null;
        this.bio = null;
        this.nposts = 0;
        this.uposts = new ArrayList<>();
    }
    
    /**
    * Construtor parametrizado.
    *@param   long id do User.
    *@param   int reputação do User.
    *@param   String nome do User.
    *@param   String biografia do User.
    *@param   int número de Posts do User.
    *@param   ArrayList<Post>  dos Posts do User.
    *@return  User criado.
    */
    public User(long id, int reputacao, String nome, String bio, int nposts, ArrayList<Post> uposts){
        this.id = id;
        this.reputacao = reputacao;
        this.nome = nome;
        this.bio = bio;
        this.nposts=nposts;
        this.uposts = new ArrayList<>();
        for(Post p: uposts)
            this.uposts.add(p);
    } 

    /**
     * Construtor por copia
     * @param User
     */
    public User(User g){
        this.id = g.getUserId();
        this.reputacao = g.getUserRep();
        this.nome = g.getUserName();
        this.bio = g.mygetUserBio();
        this.nposts = g.getUserNPosts();
        this.uposts = g.getUserPosts();
    }
    
    /**
     * Define o id do User
     * @param long
     */
    public void setUserId(long id){
        this.id = id;
    }
    
    /**
     * Define a reputaçao do User
     * @param int
     */
    public void setUserRep(int rep){
     this.reputacao = rep;   
    }
    
    /**
     * Define o nome do User
     * @param String
     */
    public void setUserName(String n){
        this.nome = n;
    }
    
    /**
     * Define a biografia do User
     * @param String
     */
    public void setUserBio(String s){
        this.bio = s;
    }
    
    /**
     * Define o número de posts publicados pelo User
     * @param int
     */
    public void setUserNPosts(int n){
        this.nposts = n;
    }
    
    /**
     * Define a lista de posts do User
     * @param ArrayList<Post>
     */
    public void setUserPosts(ArrayList<Post> uposts){
        this.uposts = new ArrayList<>();
        uposts.forEach((a)->this.uposts.add(a));
    }
    
    /**
     * Devolve o ID do user
     * @return long
     */
    public long getUserId(){
        return this.id;
    }

    /**
     * Devolve a reputação do user
     * @return int
     */
    public int getUserRep(){
        return this.reputacao;
    }

    /**
     * Devolve o nome do user
     * @return String
     */
    public String getUserName(){
        return this.nome;
    }

    /**
     * Devolve a bio do user
     * @return String
     */
    public String mygetUserBio(){
        return this.bio;
    }

    /**
     * Devolve o número de posts do user
     * @return int
     */
    public int getUserNPosts(){
        return this.nposts;
    }

    /**
     * Devolve os posts do user
     * @return ArrayList<Post> 
     */
    public ArrayList<Post> getUserPosts(){
        ArrayList<Post> posts = new ArrayList<Post>();
        for(Post p: this.uposts)
            posts.add(p);
        return posts;
    }

    /**
    * Verifica a igualdade com outro objecto
    * @param Object
    * @return boolean
    */
    public boolean equals(Object cont){
        if (this == cont) return true;
        if ( (cont == null) || (this.getClass() != cont.getClass()) ) return false;
        User c = (User) cont;
        return (this.id == c.getUserId() && this.nome.equals(c.getUserName()));
    }

    /**
     * Devolve uma cópia da instância
     * @return 
     */
    @Override
    public User clone(){
        return new User(this);
    }
    
    /**
     * Adiciona um post à lista de posts do User
     * @param Post 
     */
    public void addUserPost(Post p){
        this.uposts.add(p.clone());
    }
    
    /**
     * Incrementa o número de posts do User 
     */
    public void incNumPost(){
        int ret = this.nposts;
        ret++;
        this.nposts = ret;
    }

    /**
     * Devolve o número de posts significativos do User
     * @return int
     */
    public int getCountPosts(){
        ArrayList<Post> posts = this.getUserPosts();
        int ret = 0;
        for(Post p : posts){
            if( p.getPostType() == 1 || p.getPostType() == 2 ) ret++;
        }
        return ret;    
    }
}
