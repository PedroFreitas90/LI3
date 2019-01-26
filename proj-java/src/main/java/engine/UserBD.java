package engine;

/**
 * Classe que contém a implementação da base de dados dos Users
 *
 * @author Grupo 51
 */

import java.util.Map;
import java.util.HashMap;
import java.util.Collection;
import java.util.stream.Collectors;

public class UserBD {

    private HashMap<Long,User> usermap;

    /**
     * Construtor vazio
     */
    public UserBD(){
        this.usermap = new HashMap<Long,User>();
    }

    /**
     * Construtor parametrizado
     * @param HashMap<Long,User> 
     */
    public UserBD(HashMap<Long,User> u){
        HashMap<Long,User> usermap = new HashMap<>();
        u.entrySet().stream().forEach(entry -> usermap.put(entry.getKey(), entry.getValue()));
    }

    /**
     * Construtor de cópia
     * @param UserBD
     */
    public UserBD(UserBD u){
        usermap = u.getUserMap();
    }

    /**
     * Função que limpa a estrutura
     */    
    public void clear(){
        this.usermap.clear();
    }

    /**
     * Dado um id, devolve o user correspondente
     * @param long id
     * @return User
     */
    public User getUser(long id){
        return this.usermap.get(id);
    }
    
    /**
     * Dado um user, adiciona-o à base de dados
     * @param User
     */
    public void addUser(User u){
        this.usermap.put(u.getUserId(),u);
    }
    
    /**
     * Devolve o map que contém todos os users e respetivos id's.
     * @return HashMap<Long,User>
     */
    public HashMap<Long,User> getUserMap(){
        HashMap<Long,User> usermap = new HashMap<>();
        this.usermap.entrySet().stream().forEach(entry -> usermap.put(entry.getKey(), entry.getValue()));
        return usermap;
    }
    
    /**
     * Devolve o clone do objeto
     * @return UserBD
     */
    public UserBD clone(){
        return new UserBD(this);
    }
    
    /**
     * Verifica se dois objetos são iguais
     * @param Object
     * @return boolean
     */
    public boolean equals(Object o){
        if(this==o) return true;
        
        if(o==null || o.getClass() != this.getClass()) return false;
        
        UserBD bd = (UserBD) o;
        return bd.getUserMap().equals(this.usermap);
    }
}
