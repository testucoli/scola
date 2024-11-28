public class Parcheggio {
    private String nomeParcheggio;
    private int capienza;
    private boolean[] posti;
    
    public Parcheggio(String nomeParcheggio, int capienza){
        this.nomeParcheggio= nomeParcheggio;
        this.capienza=capienza;
        this.posti=new boolean[capienza];
    }
    public Parcheggio(Parcheggio p){
        this.nomeParcheggio=p.getNomeParcheggio();
        this.capienza=p.getCapienza();
        this.posti=p.getPosti();
    }
    
    public String getNomeParcheggio(){
        return this.nomeParcheggio;
    }
    public int getCapienza(){
        return this.capienza;
    }
    public boolean[] getPosti(){
        boolean[] p=new boolean[this.capienza]; 
        for(int i=0; i<this.capienza;i++){
            p[i]= this.posti[i];
        }
        return p;
    }
    
    public void setNomeParcheggio(String nomeParcheggio){
        this.nomeParcheggio=nomeParcheggio;
    }
    public void setCapienza(int capienza){
        this.capienza=capienza;
    }
    
    public void setPosti(boolean[] posti){
        for(int i=0;i<this.capienza;i++){
            this.posti[i]=posti[i];
        }
    }
    public boolean occupaPosto(int p){
        if(!this.posti[p]){
            this.posti[p]=true;
            return true;
        }
        else{
            return false;
        }
    }
    public boolean liberaPosto(int p){
        if(this.posti[p]){
            this.posti[p]=false;
            return true;
        }
        else{
            return false;
        }
    }
    public boolean occupaPosto(){
        for(int i=0;i<this.capienza;i++){
            if(!posti[i]){
                this.posti[i]=true;
                return true;
            }
        }
        return false;
        
    }
    public int postiLiberi(){
        int k=0;
        for(int i=0;i<this.capienza;i++){
            if(!posti[i]){
               k++;
            }
            
        }
        return k;
    }
    
    public String toString(){
        String s = "";
        s += "Nome parcheggio: " + this.nomeParcheggio + "\n";
        s += "Capienza: " + this.capienza + "\n";
        s += "Posti: ";
        for(int i=0;i<this.capienza;i++){
            s+= this.posti[i] + " ";
        }
        return s;
    }
    
    public boolean equals(Parcheggio p){
        if(!(this.nomeParcheggio.equals(p.getNomeParcheggio()))){
            return false;
        }
        if(this.capienza != p.getCapienza()){
            return false;
        }
        for(int i=0;i<this.capienza;i++){
            if(this.posti[i]!=p.getPosti()[i]){
                return false;
            }
        }
        
        return true;
        
    }
}
