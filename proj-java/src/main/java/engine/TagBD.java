package engine;

/**
 * Classe que contém a implementação da base de dados das Tags
 *
 * @author Grupo 51
 */

import java.util.Map;
import java.util.HashMap;
import java.util.Collection;
import java.util.stream.Collectors;

public class TagBD {

    private HashMap<Long,Tag> tagmap;

    /**
     * Construtor vazio
     */
    public TagBD(){
        this.tagmap = new HashMap<Long,Tag>();
    }

    /**
     * Construtor parametrizado
     * @param HashMap<Long,Tag> 
     */
    public TagBD(HashMap<Long,Tag> t){
        HashMap<Long,Tag> tagmap = new HashMap<>();
        t.entrySet().stream().forEach(entry -> tagmap.put(entry.getKey(), entry.getValue()));
    }   

    /**
     * Construtor de cópia
     * @param TagBD
     */
    public TagBD(TagBD u){
        tagmap = u.getTagMap();
    }

    /**
     * Função que limpa a estrutura
     */
    public void clear(){
        this.tagmap.clear();
    }
    
    /**
     * Dada uma tag, adiciona-a à base de dados
     * @param Tag
     */
    public void addTag(Tag u){
        this.tagmap.put(u.getTagId(),u);
    }
    
    /**
     * Devolve o map que contém todas as tags e respetivos id's.
     * @return HashMap<Long,Tag>
     */
    public HashMap<Long,Tag> getTagMap(){
        HashMap<Long,Tag> tagmap = new HashMap<>();
        this.tagmap.entrySet().stream().forEach(entry -> tagmap.put(entry.getKey(), entry.getValue()));
        return tagmap;
    }
    
    /**
     * Devolve o clone do objeto
     * @return TagBD
     */
    public TagBD clone(){
        return new TagBD(this);
    }
    
    /**
     * Verifica se dois objetos são iguais
     * @param Object
     * @return boolean
     */
    public boolean equals(Object o){
        if(this==o) return true;
        
        if(o==null || o.getClass() != this.getClass()) return false;
        
        TagBD bd = (TagBD) o;
        return bd.getTagMap().equals(this.tagmap);
    }
}
